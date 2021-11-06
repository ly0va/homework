// Потьомкiн Лев, Лабораторна 3, мова JavaScript

import java.io.*;
import java.nio.file.*;
import java.util.regex.*;

public class Lab3 {
    // TODO: handle errors / unexpected symbols, tokenize with whitespace in between indentifiers: 111aaa - illegal
    public static enum LexemeType {
        Whitespace("[\t\n\r ]+"),
        Number("[0-9]+(\\.[0-9]+)?(e[+-]?[0-9]+)?"),
        String("\"[^\"]*\"|'[^']*'|`[^`]*`"),
        Comment("//.*"),
        Keyword("break|case|catch|class|const|continue|debugger|default|delete|do|else|export|extends|finally|for|function|if|import|in|instanceof|new|return|super|switch|this|throw|try|typeof|var|void|while|with|yield"),
        Identifier("[a-zA-Z_$][a-zA-Z_$0-9]*"),
        Operator("(\\+\\+|\\+|--|-|\\*\\*|/|%|\\*|<<|<|>>>|>>|>|==|=|!=|!|&&|\\^|\\|\\||&|\\||\\?\\?)=?|~"),
        Punctuation("[;:,\\.\\{\\}\\[\\]\\(\\)]");

        public final String pattern;

        private LexemeType(String pattern) {
            this.pattern = pattern;
        }
    };

    public static void main(String[] args) {
        String filename = args.length < 2 ? "source.js" : args[1];
        parseCode(filename);
    }

    public static void parseCode(String filename) {
        String source;
        try {
            source = Files.readString(Path.of(filename));
        } catch (IOException e) {
            System.err.println(e);
            return;
        }

        StringBuffer patternsBuffer = new StringBuffer();
        for (LexemeType type : LexemeType.values()) {
            patternsBuffer.append(String.format("|(%s)", type.pattern));
        }

        Pattern pattern = Pattern.compile(new String(patternsBuffer.substring(1)));
        Matcher matcher = pattern.matcher(source);

        while (matcher.find()) {
            for (LexemeType type: LexemeType.values()) {
                if (matcher.group().matches(type.pattern)) {
                    if (type != LexemeType.Whitespace && type != LexemeType.Comment) {
                        System.out.println(matcher.group() + " - " + type.name());
                    }
                    break;
                }
            }
        }
    }
}
