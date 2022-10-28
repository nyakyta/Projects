class Options:

    def __init__(self, is_cezar=0, is_vigener=0, is_encrypt=0, key=-1, text="", is_own=0, know_key=0, most_freq="",
                 alphabet="", str_key=""):
        self.alphabet = alphabet
        self.is_encrypt = is_encrypt
        self.key = key
        self.str_key = str_key
        self.is_cezar = is_cezar
        self.is_vigener = is_vigener
        self.is_own = is_own
        self.know_key = know_key
        self.most_freq = most_freq
        self.text = text
        self.str_buttons = ["шифр Цезаря", "шифр Виженера", "Главное меню", "Зашифровать"
                            "Дешифровать", "Да, свой", "Латиница или кириллица", "Да, есть",
                            "Нет("]