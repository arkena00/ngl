package psi;

import com.intellij.extapi.psi.PsiFileBase;
import com.intellij.openapi.fileTypes.FileType;
import com.intellij.psi.FileViewProvider;
import ngl.*;
import org.jetbrains.annotations.NotNull;

import javax.swing.*;

public class ngl_file extends PsiFileBase {
    public ngl_file(@NotNull FileViewProvider viewProvider) {
        super(viewProvider, ngl.INSTANCE);
    }

    @NotNull
    @Override
    public FileType getFileType() {
        return ngl_file_type.INSTANCE;
    }

    @Override
    public String toString() {
        return "ngl File";
    }

    @Override
    public Icon getIcon(int flags) {
        return super.getIcon(flags);
    }
}