

class Decrypt:

    def __init__(self, is_encrypt=1, key=-1, str_key="", alphabet="", text=""):
        self.rus_alp_high = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
        self.rus_alp_low = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
        self.rus_most_freq = "о"

        self.lat_alp_high = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        self.lat_alp_low = "abcdefghijklmnopqrstuvwxyz"
        self.lat_most_freq = "e"

        self.alphabet = alphabet
        self.is_encrypt = is_encrypt
        self.key = key
        self.str_key = str_key
        self.text = text
        self.cypher_text = None

    def cypher(self):
        self.cypher_text = ""
