#!/usr/bin/python3

PROMPT = '''
Pick an option:
1) UAH to USD
2) USD to UAH
3) UAH to EUR
4) EUR to UAH
> '''

class Converter:

    def __init__(self, usd: float, eur: float):
        self._usd = usd
        self._eur = eur

    def USDtoUAH(self, amount: float):
        return amount * self._usd

    def UAHtoUSD(self, amount: float):
        return amount / self._usd

    def EURtoUAH(self, amount: float):
        return amount * self._eur

    def UAHtoEUR(self, amount: float):
        return amount / self._eur


if __name__ == '__main__':
    usd = float(input('USD: '))
    eur = float(input('EUR: '))
    converter = Converter(usd, eur)
    jumpTable = {
        '1': converter.UAHtoUSD,
        '2': converter.USDtoUAH,
        '3': converter.UAHtoEUR,
        '4': converter.EURtoUAH
    }
    option = input(PROMPT)
    if option not in list('1234'):
        print('Wrong option!')
    else:
        amount = float(input('Amount: '))
        print('Converted:', jumpTable[option](amount))
    
