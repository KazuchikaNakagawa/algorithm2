import wikipedia
import random
"""
# set the language japanese

page = wikipedia.page("アルゴリズム")
print(page.links)

# extract reference links and store them in a list
references = []"""

class WikiVertex:
    def __init__(self, word, identifier, links):
        self.word = word
        self.links = list(links)
        self.identifier = identifier
    def decode(self, graph):
        result = self.word + "(" + str(self.identifier) + "): "
        for link in self.links:
            result += "-> " + str(link) + ", "
        return result
    def exportToCSV(self):
        with open(f"vertex{self.identifier}.csv", "w") as f:
            f.write(self.word + "," + str(len(self.links)) + "," + ",".join(map(str, self.links)) + "\n")

class WikiGraph:
    def __init__(self, depth, initial_word):
        wikipedia.set_lang("ja")
        self.word2index = {}
        self.word_count = 0
        self.vertex_list = []
        self.create_graph(depth, initial_word)
    
    def get_index(self, word):
        print(word+" searched")
        if word not in self.word2index:
            self.word2index[word] = self.word_count
            self.word_count += 1
        return self.word2index[word]

    def create_graph(self, depth, word):
        try:
            page = wikipedia.page(word)
        except:
            if word in self.word2index:
                del self.word2index[word]
            return
        sampleN = min(random.randint(1,3), len(page.links), depth)
        depth = max(depth - sampleN, 0)
        links = random.sample(page.links, sampleN) + list(set(self.word2index.keys()) & set(page.links))
        identifier = self.get_index(word)
        for link in links:
            if link not in self.word2index:
                self.create_graph(depth, link)

        vertex = WikiVertex(word, identifier, map(self.get_index, links))
        self.vertex_list.append(vertex)
    def __repr__(self) -> str:
        result = ""
        for vertex in self.vertex_list:
            result += vertex.decode(self) + "\n"
        return result
    def exportCSVEncoder(self):
        # export word2index to csv
        with open("word2index.csv", "w") as f:
            for word, index in self.word2index.items():
                f.write(word + "," + str(index) + "\n")
        # export every vertex to csv
        for vertex in self.vertex_list:
            vertex.exportToCSV()
        
print("this program has finished")
exit()
graph = WikiGraph(15, "アルゴリズム")
print(graph)
graph.exportCSVEncoder()