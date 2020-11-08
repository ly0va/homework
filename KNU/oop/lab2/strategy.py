#!/usr/bin/python3

import xml.dom.minidom as dom
import xml.sax as sax

FIELDS = ['title', 'artist', 'country', 'company', 'price', 'year']
MAIN_TAG = 'cd'

class DOMParser:
    @staticmethod
    def parse(xml):
        dom_tree = dom.parseString(xml)
        collection = dom_tree.documentElement
        cds = []
        for node in collection.getElementsByTagName(MAIN_TAG):
            cd = {}
            for field in FIELDS:
                element = node.getElementsByTagName(field)[0]
                cd[field] = element.childNodes[0].data
            cds.append(cd)
        return cds


class Handler(sax.ContentHandler):
    def __init__(self):
        self.current_tag = ""
        self.current_element = {}
        self.elements = []

    def startElement(self, tag, attributes):
        self.current_tag = tag
        if tag == MAIN_TAG:
            self.current_element.update(attributes)

    def endElement(self, tag):
        if tag == MAIN_TAG:
            self.elements.append(self.current_element)
            self.current_element = {}
        self.current_tag = ""

    def characters(self, content):
        if self.current_tag in FIELDS:
            self.current_element[self.current_tag] = content

class SAXParser:
    @staticmethod
    def parse(xml):
        handler = Handler()
        sax.parseString(xml, handler)
        return handler.elements

