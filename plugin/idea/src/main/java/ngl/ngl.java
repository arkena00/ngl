package ngl;

import com.intellij.lang.Language;

public class ngl extends Language {
    public static final ngl INSTANCE = new ngl();

    private ngl() {
        super("ngl");
    }
}