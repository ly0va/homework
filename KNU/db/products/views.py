# -*- coding: utf-8 -*-
from django.views.generic import ListView, DetailView 
from django.contrib.messages.views import SuccessMessageMixin
from django.views.generic.edit import CreateView, UpdateView, DeleteView
from django.http import HttpResponse
from django.urls import reverse_lazy
from django.shortcuts import render
from collections import namedtuple
from django.db import connection
from .models import *
from .forms import *

def index(request):
    return render(request, 'products/index.html', context={})

def namedtuplefetchall(cursor):
    desc = cursor.description
    nt_result = namedtuple('Result', [col[0] for col in desc])
    return [nt_result(*row) for row in cursor.fetchall()]

def query(request):
    results = []
    if request.method == 'POST':
        with connection.cursor() as cursor:
            form1 = NameForm(request.POST)
            form2 = SymbolForm(request.POST)
            form3 = AmountForm(request.POST)
            form4 = AmountForm1(request.POST)
            form5 = AmountForm2(request.POST)
            form6 = AmountForm3(request.POST)
            form7 = SpecialForm1(request.POST)
            form8 = SpecialForm2(request.POST)
            if form1.is_valid():
                name = form1.cleaned_data.get("name")
                cursor.execute(f"""
                   SELECT MAX(amount) as amount FROM income 
                   INNER JOIN category ON category_id = category.id
                   WHERE category.name = '{name}'
                """)
            elif form2.is_valid():
                symbol = form2.cleaned_data.get("symbol")
                cursor.execute(f"""
                    SELECT account.name FROM account
                    INNER JOIN currency ON currency_id = currency.id 
                    WHERE symbol = '{symbol}'
                """)
            elif form3.is_valid():
                amount = form3.cleaned_data.get("amount")
                cursor.execute(f"""
                    SELECT account.name FROM account 
                    INNER JOIN income ON income.account_id = account.id 
                    GROUP BY account.id 
                    HAVING SUM(income.amount) > {amount}
                """)
            elif form4.is_valid():
                amount = form4.cleaned_data.get("amount1")
                cursor.execute(f"""
                    SELECT currency.symbol FROM 
                        (account INNER JOIN income ON income.account_id = account.id)
                        INNER JOIN currency ON account.currency_id = currency.id
                        WHERE income.amount < 0
                        GROUP BY account.id HAVING -AVG(income.amount) < {amount}
                """)
            elif form5.is_valid():
                amount = form5.cleaned_data.get("amount2")
                cursor.execute(f"""
                    SELECT category.name FROM 
                        (account INNER JOIN income ON income.account_id = account.id)
                        INNER JOIN category ON income.category_id = category.id
                        GROUP BY category.id HAVING COUNT(DISTINCT account.id) >= {amount}
                """)
            elif form6.is_valid():
                amount = form6.cleaned_data.get("amount3")
                cursor.execute(f"""
                    SELECT DISTINCT account.name FROM account 
                    INNER JOIN income ON income.account_id = account.id 
                    WHERE income.category_id IN (
                        SELECT I.category_id FROM income as I 
                        WHERE I.account_id = {amount}
                    )
                """)
            elif form7.is_valid():
                acc_number = form7.cleaned_data.get("acc_number")
                symbol = form7.cleaned_data.get("curr")
                cursor.execute(f"""
                    SELECT DISTINCT to_acc.name FROM
                    ((account AS to_acc INNER JOIN transfer ON transfer.to_account_id = to_acc.id) 
                    INNER JOIN account AS from_acc ON transfer.from_account_id = from_acc.id)
                    INNER JOIN currency ON currency.id = from_acc.currency_id 
                    WHERE currency.symbol = '{symbol}'
                    GROUP BY to_acc.id
                    HAVING COUNT(DISTINCT transfer.id) >= {acc_number}
                """)
            elif form8.is_valid():
                acc_name = form8.cleaned_data.get("acc_name")
                cursor.execute(f"""
                    SELECT DISTINCT category.name FROM category INNER JOIN
                    (SELECT category_id, currency_id FROM 
                        income INNER JOIN account ON account.id = income.account_id
                        GROUP BY category_id
                        HAVING COUNT(DISTINCT currency_id) > 1
                    ) ON category_id = category.id 
                    WHERE currency_id IN (SELECT A.currency_id FROM account AS A where A.name = '{acc_name}')
                """)
            results = namedtuplefetchall(cursor);
    form1 = NameForm()
    form2 = SymbolForm()
    form3 = AmountForm()
    form4 = AmountForm1()
    form5 = AmountForm2()
    form6 = AmountForm3()
    form7 = SpecialForm1()
    form8 = SpecialForm2()
    return render(request, 'products/queries.html', context={
        "form1": form1,
        "form2": form2,
        "form3": form3,
        "form4": form4,
        "form5": form5,
        "form6": form6,
        "form7": form7,
        "form8": form8,
        "results": results
    })

class CurrencyList(ListView):
    model = Currency

class CurrencyDetail(DetailView):
    model = Currency

class CurrencyCreate(SuccessMessageMixin, CreateView): 
    model = Currency
    form_class = CurrencyForm
    success_url = reverse_lazy('currency_list')
    success_message = "Currency successfully created!"

class CurrencyUpdate(SuccessMessageMixin, UpdateView): 
    model = Currency
    form_class = CurrencyForm
    success_url = reverse_lazy('currency_list')
    success_message = "Currency successfully updated!"

class CurrencyDelete(SuccessMessageMixin, DeleteView):
    model = Currency
    success_url = reverse_lazy('currency_list')
    success_message = "Currency successfully deleted!"

class CategoryList(ListView): 
    model = Category

class CategoryDetail(DetailView): 
    model = Category

class CategoryCreate(SuccessMessageMixin, CreateView): 
    model = Category
    form_class = CategoryForm
    success_url = reverse_lazy('category_list')
    success_message = "Category successfully created!"

class CategoryUpdate(SuccessMessageMixin, UpdateView): 
    model = Category
    form_class = CategoryForm
    success_url = reverse_lazy('category_list')
    success_message = "Category successfully updated!"

class CategoryDelete(SuccessMessageMixin, DeleteView):
    model = Category
    success_url = reverse_lazy('category_list')
    success_message = "Category successfully deleted!"

class AccountList(ListView): 
    model = Account

class AccountDetail(DetailView): 
    model = Account

class AccountCreate(SuccessMessageMixin, CreateView): 
    model = Account
    form_class = AccountForm
    success_url = reverse_lazy('account_list')
    success_message = "Account successfully created!"

class AccountUpdate(SuccessMessageMixin, UpdateView): 
    model = Account
    form_class = AccountForm
    success_url = reverse_lazy('account_list')
    success_message = "Account successfully updated!"

class AccountDelete(SuccessMessageMixin, DeleteView):
    model = Account
    success_url = reverse_lazy('account_list')
    success_message = "Account successfully deleted!"

class TransferList(ListView): 
    model = Transfer

class TransferDetail(DetailView): 
    model = Transfer

class TransferCreate(SuccessMessageMixin, CreateView): 
    model = Transfer
    form_class = TransferForm
    success_url = reverse_lazy('transfer_list')
    success_message = "Transfer successfully created!"

class TransferUpdate(SuccessMessageMixin, UpdateView): 
    model = Transfer
    form_class = TransferForm
    success_url = reverse_lazy('transfer_list')
    success_message = "Transfer successfully updated!"

class TransferDelete(SuccessMessageMixin, DeleteView):
    model = Transfer
    success_url = reverse_lazy('transfer_list')
    success_message = "Transfer successfully deleted!"

class IncomeList(ListView): 
    model = Income

class IncomeDetail(DetailView): 
    model = Income

class IncomeCreate(SuccessMessageMixin, CreateView): 
    model = Income
    form_class = IncomeForm
    success_url = reverse_lazy('income_list')
    success_message = "Income successfully created!"

class IncomeUpdate(SuccessMessageMixin, UpdateView): 
    model = Income
    form_class = IncomeForm
    success_url = reverse_lazy('income_list')
    success_message = "Income successfully updated!"

class IncomeDelete(SuccessMessageMixin, DeleteView):
    model = Income
    success_url = reverse_lazy('income_list')
    success_message = "Income successfully deleted!"
