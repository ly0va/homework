# -*- coding: utf-8 -*-
from django import forms

from .models import *

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
