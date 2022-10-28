from decrypt import Decrypt


class Cezar(Decrypt):

    def __init__(self, is_encrypt=1, key=-1, alphabet="", text="", most_freq=""):
        super().__init__(is_encrypt, key, alphabet, text)
        self.most_freq = most_freq

    def cezar_symbol(self, cur_alphabet, text_symbol):
        return cur_alphabet[(cur_alphabet.find(text_symbol) + self.key * self.is_encrypt) % len(cur_alphabet)]

    def freq_analys(self):
        most_freq_cur = 0
        most_freq_symbol = ""
        copy_text = self.text.lower()
        for i in range(len(copy_text)):
            if (copy_text[i] in self.lat_alp_high or self.lat_alp_low or self.rus_alp_high
                    or self.rus_alp_low or (self.alphabet and self.alphabet != "")):
                if copy_text.count(copy_text[i]) >= most_freq_cur:
                    most_freq_symbol = copy_text[i]
                    most_freq_cur = copy_text.count(copy_text[i])
        if most_freq_symbol in self.alphabet and self.alphabet != "":
            self.key = (self.alphabet.find(most_freq_symbol)
                        - self.alphabet.find(self.most_freq)) % len(self.alphabet)
        elif most_freq_symbol in self.lat_alp_low:
            self.key = (self.alphabet.find(most_freq_symbol)
                        - self.alphabet.find(self.lat_most_freq)) % len(self.lat_alp_low)
        elif most_freq_symbol in self.rus_alp_low:
            self.key = (self.rus_alp_low.find(most_freq_symbol)
                        - self.rus_alp_low.find(self.rus_most_freq)) % len(self.rus_alp_low)

    def cypher(self):
        super().cypher()
        if self.key == -1:
            self.freq_analys()
        for i in range(len(self.text)):
            if (self.text[i] in self.alphabet) and self.alphabet != "":
                self.cypher_text += self.cezar_symbol(self.alphabet, self.text[i])
            elif self.text[i] in self.lat_alp_high:
                self.cypher_text += self.cezar_symbol(self.lat_alp_high, self.text[i])
            elif self.text[i] in self.lat_alp_low:
                self.cypher_text += self.cezar_symbol(self.lat_alp_low, self.text[i])
            elif self.text[i] in self.rus_alp_high:
                self.cypher_text += self.cezar_symbol(self.rus_alp_high, self.text[i])
            elif self.text[i] in self.rus_alp_low:
                self.cypher_text += self.cezar_symbol(self.rus_alp_low, self.text[i])
            else:
                self.cypher_text += self.text[i]
        return self.cypher_text
