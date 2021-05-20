# -*- coding: utf-8 -*-
from django.views.generic import ListView, DetailView 
from django.contrib.messages.views import SuccessMessageMixin
from django.views.generic.edit import CreateView, UpdateView, DeleteView
from django.http import HttpResponse
from django.urls import reverse_lazy
from django.shortcuts import render

from .models import *
from .forms import *

def index(request):
    return render(request, 'knox/index.html', context={})

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
