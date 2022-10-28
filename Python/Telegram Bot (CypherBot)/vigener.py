from decrypt import Decrypt


class Vigener(Decrypt):

    def __init__(self, is_encrypt=1, str_key="", alphabet="", text=""):
        super().__init__(is_encrypt=is_encrypt, str_key=str_key, alphabet=alphabet, text=text)

    def vigener_symbol(self, alp, text_symbol, key_symbol):
        return alp[(alp.find(text_symbol) + self.alphabet.find(key_symbol) * self.is_encrypt) % len(alp)]

    def cypher(self):
        super().cypher()
        text_len = 0
        for i in range(len(self.text)):
            if (self.text[i] in self.alphabet) and self.alphabet != "":
                self.cypher_text += self.vigener_symbol(self.alphabet, self.text[i],
                                                        self.str_key[text_len % len(self.str_key)])
            elif self.text[i] in self.lat_alp_high:
                self.cypher_text += self.vigener_symbol(self.lat_alp_high, self.text[i],
                                                        self.str_key[text_len % len(self.str_key)])
            elif self.text[i] in self.lat_alp_low:
                self.cypher_text += self.vigener_symbol(self.lat_alp_low, self.text[i],
                                                        self.str_key[text_len % len(self.str_key)])
            elif self.text[i] in self.rus_alp_high:
                self.cypher_text += self.vigener_symbol(self.rus_alp_high, self.text[i],
                                                        self.str_key[text_len % len(self.str_key)].upper())
            elif self.text[i] in self.rus_alp_low:
                self.cypher_text += self.vigener_symbol(self.rus_alp_low, self.text[i],
                                                        self.str_key[text_len % len(self.str_key)].lower())
            else:
                self.cypher_text += self.text[i]
                text_len -= 1
            text_len += 1
        return self.cypher_text
