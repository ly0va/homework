
import java.nio.file.*;
import java.io.*;

public class Lab4 {
    private final String[] keywords = {
        "break", "case", "catch", "class", "const", "continue", "debugger", "default", "delete", "do", "else", 
        "export", "extends", "finally", "for", "function", "if", "import", "in", "instanceof", "let", "new", "return", 
        "super", "switch", "this", "throw", "try", "typeof", "var", "void", "while", "with", "yield"
    };
    private final String[] operators = {
        "+=", "-=", "**=", "/=", "%=", "*=", "<<=", "<=", ">>>=", ">>=", ">=", "===", "!==", "&&=", "&=", "^=", "||=", "|=", "??=",
        "++", "--", "**", "/", "%", "*", "<<", "<", ">>>", ">>", ">", "==", "=", "!=", "!", "&&", "&", "^", "||", "|", "??",
        "+", "-", "~", "?"
    };
    private final String punctuation = ".,:;()[]{}";

    private String buffer = "";

    private static enum State {
        None,
        String, 
        Number,
        Identifier,
        Comment,
        Error,
        End,
    }

    private State state = State.None;
    private boolean decimalPoint = false;
    private boolean decimalExponent = false;

    public static void main(String[] args) {
        String filename = args.length < 2 ? "source.js" : args[1];

        String source = "";
        try {
            source = Files.readString(Path.of(filename));
        } catch (IOException e) {
            System.err.println(e);
        }

        new Lab4().parseCode(source);
    }

    public void parseCode(String text) {
        int i = 0;
        while (state != State.End) {
            if (i >= text.length()) {
                if (state == State.None) {
                    state = State.End;
                    System.out.println("\nParsed successfully");
                } else {
                    state = State.Error;
                    System.err.println("\nUnexpected end of file");
                }
                break;
            }

            char symbol = text.charAt(i);
            String operator;

            switch (state) {
                case None:
                    buffer = "";
                    if (Character.isWhitespace(symbol)) {
                        // found whitespace
                    } else if (punctuation.contains(""+symbol)) {
                        // found punctuation
                        log(""+symbol, "Punctuation");
                    } else if (symbol == '/' && text.length() > i+1 && text.charAt(i+1) == '/') {
                        // found comment
                        state = State.Comment;
                        buffer += "//";
                        i++;
                    } else if ((operator = startsWithOneOf(text.substring(i), operators)) != null) {
                        // found operator
                        log(operator, "Operator");
                        i += operator.length() - 1;
                    } else if ("$_".contains(""+symbol) || Character.isLetter(symbol)) {
                        // found indentifier
                        state = State.Identifier;
                        buffer += symbol;
                    } else if ("\"'`".contains(""+symbol)) {
                        // found string
                        state = State.String;
                        buffer += symbol;
                    } else if (Character.isDigit(symbol)) {
                        // found number
                        state = State.Number;
                        buffer += symbol;
                    } else {
                        state = State.Error;
                        buffer += symbol;
                    }
                    i++;
                    break;
                case Identifier:
                    if (Character.isLetter(symbol) || Character.isDigit(symbol) || "$_".contains(""+symbol)) {
                        buffer += symbol;
                        i++;
                    } else {
                        if (contains(keywords, buffer)) {
                            // found keyword
                            log(buffer, "Keyword");
                        } else {
                            log(buffer, "Identifier");
                        }
                        state = State.None;
                    }
                    break;
                case String:
                    buffer += symbol;
                    if ("\"'`".contains(""+symbol)) {
                        log(buffer, "String");
                        state = State.None;
                    }
                    i++;
                    break;
                case Number:
                    if (Character.isDigit(symbol)) {
                        buffer += symbol;
                        i++;
                    } else if (symbol == '.') {
                        if (decimalPoint) {
                            state = State.Error;
                        } else {
                            decimalPoint = true;
                            buffer += symbol;
                            i++;
                        }
                    } else if ("eE".contains(""+symbol)) {
                        if (decimalExponent) {
                            state = State.Error;
                        } else {
                            decimalExponent = true;
                            buffer += symbol;
                            i++;
                        }
                    } if ("+-".contains(""+symbol)) {
                        char last = buffer.charAt(buffer.length()-1);
                        if ("eE".contains(""+last)) {
                            buffer += symbol;
                            i++;
                        } else if (last == '.') {
                            state = State.Error;
                        } else {
                            state = State.None;
                        }
                    } else {
                        try {
                            Double.parseDouble(buffer);
                            log(buffer, "Number");
                            state = State.None;
                        } catch (NumberFormatException e) {
                            state = State.Error;
                        }
                    }
                case Comment:
                    if (symbol != '\n') {
                        buffer += symbol;
                    } else {
                        state = State.None;
                    }
                    i++;
                    break;
                case Error:
                    System.err.println("\nInvalid token");
                    return;
                case End:
                    return;
            }
        }
    }

    private boolean contains(String[] haystack, String needle) {
        for (String hay: haystack) {
            if (hay.equals(needle)) return true;
        }
        return false;
    }

    private String startsWithOneOf(String text, String[] words) {
        for (String word: words) {
            if (text.startsWith(word)) return word;
        }
        return null;
    }

    private void log(String token, String type) {
        System.out.println(token + " - " + type);
    }
}
