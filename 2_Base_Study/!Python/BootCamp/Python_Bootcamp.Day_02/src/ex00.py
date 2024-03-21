

from typing import Dict, Union


class Key:
    passphrase = "zax2rulez"
    def __init__(self, key_len: int = 1337, val404: int = 3, 
                 more_then: int = 9000, 
                 passphrase: str = "zax2rulez", repr = "GeneralTsoKeycard") -> None:
        if self.check_correct_type(values=
                                   dict(key_len=key_len, 
                                        val404=val404, 
                                        more_then=more_then,
                                        passphrase=passphrase, 
                                        repr=repr)):
            self.key_len = key_len
            self.more_then = more_then
            self.passphrase = passphrase
            self.val404 = val404
            self.key_len = key_len
        else:
            raise TypeError("Неверный тип данных!")
        

    @staticmethod
    def check_correct_type(values: Dict[str, Union[str, int]]) -> bool:
        for key in values.keys():
            if key in ("key_len", "val404", "more_then"):
                if isinstance(values.get(key), int):
                    continue
                return False
            elif key in ("passphrase", "repr"):
                if isinstance(values.get(key), str):
                    continue
                return False
        return True
        
    
    def __len__(self):
        return self.key_len

    def __getitem__(self, item: int):
        return self.val404

    def __repr__(self) -> str:
        return "GeneralTsoKeycard"
    
    def __gt__(self, __value: object) -> bool:
        if __value < self.more_then + 1:
            return True
        return False
    
    

if __name__ == "__main__":
    key = Key(key_len='1000')
