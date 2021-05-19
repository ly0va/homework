# -*- coding: utf-8 -*-
from django import forms

from .models import *

class SymbolForm(forms.Form):
    symbol = forms.CharField(label='X', max_length=10)

class NameForm(forms.Form):
    name = forms.CharField(label='X', max_length=100)

class AmountForm(forms.Form):
    amount = forms.IntegerField(label='X')

class AmountForm1(forms.Form):
    amount1 = forms.IntegerField(label='X')

class AmountForm2(forms.Form):
    amount2 = forms.IntegerField(label='X')

class AmountForm3(forms.Form):
    amount3 = forms.IntegerField(label='X')

class SpecialForm1(forms.Form):
    acc_number = forms.IntegerField(label='X')
    curr = forms.CharField(label='Y', max_length=10)

class SpecialForm2(forms.Form):
    acc_name = forms.CharField(label='X', max_length=100)

class AccountForm(forms.ModelForm):
    class Meta:
        model = Account
        fields = '__all__'

class CurrencyForm(forms.ModelForm):
    class Meta:
        model = Currency
        fields = '__all__'

class TransferForm(forms.ModelForm):
    class Meta:
        model = Transfer
        fields = '__all__'

class IncomeForm(forms.ModelForm):
    class Meta:
        model = Income
        fields = '__all__'

class CategoryForm(forms.ModelForm):
    class Meta:
        model = Category
        fields = '__all__'
