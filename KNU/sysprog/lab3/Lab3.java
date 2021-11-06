// Потьомкiн Лев, Лабораторна 3, мова JavaScript

import java.io.*;
import java.nio.file.*;
import java.util.regex.*;

public class Lab3 {
    public static enum LexemeType {
        Whitespace("[\t\n\r ]+"),
        Number("\\b\\d+(\\.\\d+)?(e[+-]?\\d+)?\\b"),
        String("\"[^\"]*\"|'[^']*'|`[^`]*`"),
        Comment("//.*"),
        Keyword("\\b(break|case|catch|class|const|continue|debugger|default|delete|do|else|export|extends|finally|for|function|if|import|in|instanceof|new|return|super|switch|this|throw|try|typeof|var|void|while|with|yield)\\b"),
        Identifier("\\b[a-zA-Z_$][a-zA-Z_$0-9]*\\b"),
        Operator("(\\+\\+|\\+|--|-|\\*\\*|/|%|\\*|<<|<|>>>|>>|>|==|=|!=|!|&&|\\^|\\|\\||&|\\||\\?\\?)=?|\\?|~"),
        Punctuation("[;:,\\.\\{\\}\\[\\]\\(\\)]");

        public final String pattern;

        private LexemeType(String pattern) {
            this.pattern = pattern;
        }
    };

    public static void main(String[] args) {
        String filename = args.length < 2 ? "source.js" : args[1];
        if (parseCode(filename)) {
            System.out.println("\nParsed successfully");
        } else {
            System.out.println("\nParsing failed");
        }
    }

    public static boolean parseCode(String filename) {
        String source;
        try {
            source = Files.readString(Path.of(filename));
        } catch (IOException e) {
            System.err.println(e);
            return false;
        }

        StringBuffer patternsBuffer = new StringBuffer();
        for (LexemeType type : LexemeType.values()) {
            patternsBuffer.append(String.format("|(%s)", type.pattern));
        }

        Pattern pattern = Pattern.compile(new String(patternsBuffer.substring(1)));
        Matcher matcher = pattern.matcher(source);

        int start = 0;
        while (matcher.find()) {
            if (start != matcher.start()) {
                 System.err.println("Invalid token");
                 return false;
            } else {
                start = matcher.end();
            }
            for (LexemeType type: LexemeType.values()) {
                if (matcher.group().matches(type.pattern)) {
                    if (type != LexemeType.Whitespace && type != LexemeType.Comment) {
                        System.out.println(matcher.group() + " - " + type.name());
                    }
                    break;
                }
            }
        }

        // if (!matcher.requireEnd()) {
        //     System.err.println("Invalid token");
        //     return false;
        // }

        return true;
    }
}
