#!/usr/bin/python3
import re
import gi

gi.require_version('Gtk', '3.0')

from gi.repository import Gtk as gtk
from parser import Lexer, Parser

CELL_REGEXP = r'[A-Z][0-9]+'

class Spreadsheet(gtk.Window):

    def __init__(self, cols, rows):
        super().__init__()
        lexer = Lexer.build()
        self.parser = Parser(lexer)
        self.cols = cols
        self.rows = rows
        self.formulas = [['0'] * cols for _ in range(rows)]
        self.set_default_size(600, 600)
        self.connect('destroy', gtk.main_quit)
        self.set_title("Lyova's Spreadsheet")
        self.set_border_width(8)
        vbox = gtk.VBox(homogeneous=False, spacing=8)
        self.add(vbox)
        label = gtk.Label(label='Nice to see you here')
        vbox.pack_start(label, False, False, 0)
        sw = gtk.ScrolledWindow()
        sw.set_policy(gtk.PolicyType.NEVER, gtk.PolicyType.AUTOMATIC)
        vbox.pack_start(sw, True, True, 0)

        types = [str] * (self.cols + 1)
        self.values = gtk.ListStore(*types)
        for i in range(self.rows):
            self.values.append([' '] * self.cols + [f'<b>{i}</b>'])

        self.treeview = gtk.TreeView(model=self.values)
        sw.add(self.treeview)

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
        try:
            parsed = self.parser.parse(self.expand(text))
        except RecursionError:
            print("Cycle detected!")
        else:
            self.formulas[int(row)][cell.column] = text
            self.values[row][cell.column] = str(parsed)

    def expand(self, formula):
        def replacer(match):
            name = match[0]
            col, row = ord(name[0]) - ord('A'), int(name[1:])
            return f'({self.formulas[row][col]})'

        if not re.search(CELL_REGEXP, formula):
            return formula
        return self.expand(re.sub(CELL_REGEXP, replacer, formula))


manager = Spreadsheet(26, 30)
manager.show_all()
gtk.main()


