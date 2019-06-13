package ngl;

import com.intellij.lexer.FlexAdapter;

import java.io.Reader;

public class ngl_lexer_adapter extends FlexAdapter {
    public ngl_lexer_adapter() {
        super(new ngl_lexer((Reader) null));
    }
}