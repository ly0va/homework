# -*- coding: utf-8 -*-
from django.views.generic import ListView, DetailView 
from django.contrib.messages.views import SuccessMessageMixin
from django.views.generic.edit import CreateView, UpdateView, DeleteView
from django.http import HttpResponse
from django.urls import reverse_lazy
from django.shortcuts import render
from django.db.models import Count, Sum, Q

from .models import *
from .forms import *

def index(request):
    # SELECT category.name, COUNT(income.id) FROM 
    # income INNER JOIN category ON income.category_id = category.id
    # GROUP BY category.id
    result = Category.objects.annotate(num_payments=Count('income'))
    income_by_category = {c.name: c.num_payments for c in result}

    # SELECT account.name, SUM(income.amount) FROM
    # income INNER JOIN account ON income.account_id = account.id
    # WHERE income.amount > 0
    # GROUP BY account.id
    result = Account.objects.annotate(total=Sum('income__amount', filter=Q(income__amount__gt=0)))
    earnings = {a.name : a.total or 0 for a in result}
    result = Account.objects.annotate(total=Sum('income__amount', filter=Q(income__amount__lt=0)))
    spendings = {a.name : -(a.total or 0) for a in result}
    return render(request, 'knox/index.html', context={
        'income_by_category': income_by_category,
        'earnings': earnings,
        'spendings': spendings
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
