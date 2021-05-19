# -*- coding: utf-8 -*-
from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('queries', views.query, name='queries'),

    path('currencies/', views.CurrencyList.as_view(), name='currency_list'),
    path('currencies/view/<int:pk>', views.CurrencyDetail.as_view(), name='currency_view'),
    path('currencies/new', views.CurrencyCreate.as_view(), name='currency_new'),
    path('currencies/edit/<int:pk>', views.CurrencyUpdate.as_view(), name='currency_edit'),
    path('currencies/delete/<int:pk>', views.CurrencyDelete.as_view(), name='currency_delete'),

    path('accounts/', views.AccountList.as_view(), name='account_list'),
    path('accounts/view/<int:pk>', views.AccountDetail.as_view(), name='account_view'),
    path('accounts/new', views.AccountCreate.as_view(), name='account_new'),
    path('accounts/edit/<int:pk>', views.AccountUpdate.as_view(), name='account_edit'),
    path('accounts/delete/<int:pk>', views.AccountDelete.as_view(), name='account_delete'),

    path('incomes/', views.IncomeList.as_view(), name='income_list'),
    path('incomes/view/<int:pk>', views.IncomeDetail.as_view(), name='income_view'),
    path('incomes/new', views.IncomeCreate.as_view(), name='income_new'),
    path('incomes/edit/<int:pk>', views.IncomeUpdate.as_view(), name='income_edit'),
    path('incomes/delete/<int:pk>', views.IncomeDelete.as_view(), name='income_delete'),

    path('transfers/', views.TransferList.as_view(), name='transfer_list'),
    path('transfers/view/<int:pk>', views.TransferDetail.as_view(), name='transfer_view'),
    path('transfers/new', views.TransferCreate.as_view(), name='transfer_new'),
    path('transfers/edit/<int:pk>', views.TransferUpdate.as_view(), name='transfer_edit'),
    path('transfers/delete/<int:pk>', views.TransferDelete.as_view(), name='transfer_delete'),

    path('categories/', views.CategoryList.as_view(), name='category_list'),
    path('categories/view/<int:pk>', views.CategoryDetail.as_view(), name='category_view'),
    path('categories/new', views.CategoryCreate.as_view(), name='category_new'),
    path('categories/edit/<int:pk>', views.CategoryUpdate.as_view(), name='category_edit'),
    path('categories/delete/<int:pk>', views.CategoryDelete.as_view(), name='category_delete'),
]
