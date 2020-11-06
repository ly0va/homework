#!/usr/bin/python3
import gi
import lxml.etree as etree
import webbrowser

gi.require_version('Gtk', '3.0')

from gi.repository import Gtk as gtk

class UI(gtk.Window):

    def __init__(self, filename):
        super().__init__(title="XMLyova")
        with open(filename) as xml:
            self.xml = xml.read()
        self.parser_type = 'DOM'
        self.init_widgets()

    def init_widgets(self):
        self.set_default_size(1200, 600)
        self.connect('destroy', gtk.main_quit)
        panes = gtk.Box()
        panes.pack_start(self.left_pane(), True, True, 0)
        panes.pack_start(self.right_pane(), True, True, 0)
        main = gtk.VBox()
        main.pack_start(self.create_toolbar(), False, False, 0)
        main.pack_start(panes, True, True, 0)
        self.add(main)

    def left_pane(self):
        controls = gtk.VBox()
        controls.set_border_width(50)
        dom, sax = self.create_radio()
        controls.pack_start(dom, False, False, 10)
        controls.pack_start(sax, False, False, 0)
        controls.pack_end(self.create_buttons(), False, False, 10)
        return controls

    def create_radio(self):
        dom = gtk.RadioButton(label='DOM')
        sax = gtk.RadioButton(label='SAX')
        sax.join_group(dom)
        dom.connect('toggled', self.set_parser)
        sax.connect('toggled', self.set_parser)
        return dom, sax

    def create_buttons(self):
        buttons = gtk.Box()
        search = gtk.Button(label='Search')
        search.connect('clicked', self.search)
        transform = gtk.Button(label='Transform')
        transform.connect('clicked', self.transform)
        buttons.pack_start(search, True, True, 0)
        buttons.pack_start(transform, True, True, 10)
        return buttons

    def set_parser(self, widget, data=None):
        self.parser_type = widget.get_label()
        print(self.parser_type)

    def search(self, widget, data=None):
        pass

    def transform(self, widget, data=None):
        xml = etree.parse('./cdcatalog.xml')
        xslt = etree.parse('./cdcatalog.xsl')
        html = etree.XSLT(xslt)(xml)
        html_string = etree.tostring(html, pretty_print=True).decode()
        self.set_text(html_string)
        with open('./cdcatalog.html', 'w') as html_file:
            html_file.write(html_string)
        webbrowser.open_new_tab("./cdcatalog.html")

    def right_pane(self):
        window = gtk.ScrolledWindow()
        window.set_min_content_width(300)
        self.text_view = gtk.TextView()
        self.text_view.set_editable(False)
        self.text_view.set_cursor_visible(False)
        self.text_view.set_monospace(True)
        window.add(self.text_view)
        return window

    def set_text(self, text):
        buffer = gtk.TextBuffer()
        buffer.set_text(text)
        self.text_view.set_buffer(buffer)

    def create_toolbar(self):
        toolbar = gtk.Toolbar()
        quit = gtk.ToolButton(stock_id=gtk.STOCK_QUIT)
        info = gtk.ToolButton(stock_id=gtk.STOCK_ABOUT)
        toolbar.insert(quit, 0)
        toolbar.insert(info, 1)
        quit.connect("clicked", lambda _: self.confirm_exit())
        info.connect("clicked", lambda _: self.info(
            "XMLyova v0.1.0", 
            "Lab 2, Lev Potyomkin, K-27"
        ))
        return toolbar

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

    def confirm_exit(self):
        dialog = gtk.MessageDialog(
            transient_for=self,
            message_type=gtk.MessageType.QUESTION,
            buttons=gtk.ButtonsType.OK_CANCEL,
            text='Are you sure you want to quit?'
        )
        response = dialog.run()
        dialog.destroy()
        if response == gtk.ResponseType.OK:
            gtk.main_quit()

    def error(self, message):
        dialog = gtk.MessageDialog(
            transient_for=self,
            message_type=gtk.MessageType.ERROR,
            buttons=gtk.ButtonsType.CANCEL,
            text=message,
        )
        dialog.run()
        dialog.destroy()


if __name__ == '__main__':
    ui = UI('./cdcatalog.xml')
    ui.show_all()
    gtk.main()

