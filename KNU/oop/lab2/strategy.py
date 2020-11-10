#!/usr/bin/python3

import xml.dom.minidom as dom
import xml.sax as sax

FIELDS = ['title', 'artist', 'country', 'company', 'price', 'year']
MAIN_TAG = 'cd'

class DOMParser:
    def __init__(self, xml):
        self.collection = dom.parseString(xml).documentElement

    def parse(self, params):
        cds = []
        for node in self.collection.getElementsByTagName(MAIN_TAG):
            cd = {}
            approved = True
            for field in FIELDS:
                element = node.getElementsByTagName(field)[0]
                cd[field] = element.childNodes[0].data
                if params.get(field) and params[field] != cd[field]:
                    approved = False
            if approved:
                cds.append(cd)
        return cds


class Handler(sax.ContentHandler):
    def __init__(self, params):
        self.params = params
        self.current_tag = ""
        self.current_cd = {}
        self.current_approved = True
        self.cds = []

    def startElement(self, tag, attributes):
        self.current_tag = tag

    def endElement(self, tag):
        if tag == MAIN_TAG:
            if self.current_approved:
                self.cds.append(self.current_cd)
            self.current_cd = {}
            self.current_approved = True
        self.current_tag = ""

    def characters(self, content):
        if self.current_tag in FIELDS:
            self.current_cd[self.current_tag] = content
            field = self.current_tag
            if self.params.get(field) and self.params[field] != self.current_cd[field]:
                self.current_approved = False


class SAXParser:
    def __init__(self, xml):
        self.xml = xml

    def parse(self, params):
        handler = Handler(params)
        sax.parseString(self.xml, handler)
        return handler.cds

