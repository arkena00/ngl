package ngl;

import com.intellij.openapi.fileTypes.LanguageFileType;
import org.jetbrains.annotations.*;

import javax.swing.*;

public class ngl_file_type extends LanguageFileType {
    public static final ngl_file_type INSTANCE = new ngl_file_type();

    private ngl_file_type() {
        super(ngl.INSTANCE);
    }

    @NotNull
    @Override
    public String getName() {
        return "ngl file";
    }

    @NotNull
    @Override
    public String getDescription() {
        return "ngl language file";
    }

    @NotNull
    @Override
    public String getDefaultExtension() {
        return "ngl";
    }

    @Nullable
    @Override
    public Icon getIcon() {
        return ngl_icons.FILE;
    }
}