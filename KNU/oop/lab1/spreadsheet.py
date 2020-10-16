#!/usr/bin/python3
import re
import pickle
import gi

gi.require_version('Gtk', '3.0')

from gi.repository import Gtk as gtk
from parser import Lexer, Parser

CELL_REGEXP = r'[A-Z][0-9]+'

class Spreadsheet(gtk.Window):

    def __init__(self, cols, rows):
        super().__init__(title="Lyova's Spreadsheet")
        lexer = Lexer.build()
        self.parser = Parser(lexer)
        self.cols = cols
        self.rows = rows
        self.formulas = [[''] * cols for _ in range(rows)]
        self.init_widgets()
        self.add_table()

    def init_widgets(self):
        self.set_default_size(600, 600)
        self.connect('destroy', gtk.main_quit)
        self.set_border_width(8)
        self.window = gtk.ScrolledWindow()
        self.window.set_policy(gtk.PolicyType.NEVER, gtk.PolicyType.AUTOMATIC)
        self.treeview = gtk.TreeView()
        self.window.add(self.treeview)
        self.entry = gtk.Entry()
        vbox = gtk.VBox(homogeneous=False, spacing=8)
        vbox.pack_start(self.create_toolbar(), False, False, 0)
        vbox.pack_start(self.entry, False, False, 0)
        vbox.pack_start(self.window, True, True, 0)
        self.add(vbox)

    def create_toolbar(self):
        toolbar = gtk.Toolbar()
        load = gtk.ToolButton(stock_id=gtk.STOCK_OPEN)
        save = gtk.ToolButton(stock_id=gtk.STOCK_SAVE)
        quit = gtk.ToolButton(stock_id=gtk.STOCK_QUIT)
        info = gtk.ToolButton(stock_id=gtk.STOCK_ABOUT)
        toolbar.insert(load, 0)
        toolbar.insert(save, 1)
        toolbar.insert(quit, 2)
        toolbar.insert(info, 3)
        load.connect("clicked", lambda _: self.load())
        save.connect("clicked", lambda _: self.save())
        quit.connect("clicked", gtk.main_quit)
        info.connect("clicked", lambda _: self.info(
            "Lyova's Spreadsheet v0.1.0", 
            "Lab 1. Ticket 20. Lev Potyomkin, K-27"
        ))
        return toolbar

    def save(self):
        try:
            with open('spreadsheet.pkl', 'wb') as file:
                pickle.dump(self.formulas, file)
            self.info("File saved successfully")
        except Exception:
            self.error("Error saving file :(")

    def load(self):
        try:
            with open('spreadsheet.pkl', 'rb') as file:
                self.formulas = pickle.load(file)
            self.recalculate()
            self.info("File loaded successfully")
        except Exception:
            self.error("Error loading file :(")

    def recalculate(self):
        for i in range(self.rows):
            for j in range(self.cols):
                self.parse(i, j, self.formulas[i][j])

    def parse(self, row, col, text):
        if text == '':
            self.formulas[row][col] = ''
            self.values[str(row)][col] = ''
            return
        old_formula = self.formulas[row][col]
        self.formulas[row][col] = text
        try:
            parsed = self.parser.parse(self.expand(text))
            self.values[str(row)][col] = str(parsed)
        except RecursionError:
            self.error("Cycle detected!")
            self.formulas[row][col] = old_formula
        except SyntaxError as error:
            self.error(error.args[0])
            self.formulas[row][col] = old_formula
                

    def add_table(self):
        types = [str] * (self.cols + 1)
        self.values = gtk.ListStore(*types)
        spaces = [' '] * self.cols
        for i in range(self.rows):
            self.values.append(spaces.copy() + [f'<b>{i}</b>'])

        self.treeview.set_model(self.values)

        for i in range(self.cols):
            cell = gtk.CellRendererText()
            cell.set_property("editable", True)
            cell.connect("edited", self.update)
            cell.column = i
            header = chr(ord('A')+i)+' '*5
            column = gtk.TreeViewColumn(header, cell, text=i)
            self.treeview.append_column(column)

        cell = gtk.CellRendererText()
        cell.set_sensitive(False)
        column = gtk.TreeViewColumn('#', cell, markup=self.cols)
        self.treeview.insert_column(column, 0)
        self.treeview.set_grid_lines(3)

    def update(self, cell, row, text):
        row, col = int(row), cell.column
        self.parse(row, col, text)
        self.recalculate()

    def expand(self, formula):
        def replacer(match):
            name = match[0]
            col, row = ord(name[0]) - ord('A'), int(name[1:])
            return f'({self.formulas[row][col] or "0"})'

        if not re.search(CELL_REGEXP, formula):
            return formula
        return self.expand(re.sub(CELL_REGEXP, replacer, formula))

    def info(self, primary, secondary=''):
        dialog = gtk.MessageDialog(
            transient_for=self,
            message_type=gtk.MessageType.INFO,
            buttons=gtk.ButtonsType.OK,
            text=primary,
        )
        dialog.format_secondary_text(secondary)
        dialog.run()
        dialog.destroy()

    def error(self, message):
        dialog = gtk.MessageDialog(
            transient_for=self,
            message_type=gtk.MessageType.ERROR,
            buttons=gtk.ButtonsType.CANCEL,
            text=message,
        )
        dialog.run()
        dialog.destroy()


spreadsheet = Spreadsheet(26, 30)
spreadsheet.show_all()
gtk.main()


