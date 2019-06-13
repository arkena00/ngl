package psi;

import com.intellij.psi.tree.IElementType;
import ngl.ngl;
import org.jetbrains.annotations.*;

public class ngl_token_type extends IElementType {
    public ngl_token_type(@NotNull @NonNls String debugName) {
        super(debugName, ngl.INSTANCE);
    }

    @Override
    public String toString() {
        return "ngl_token_type." + super.toString();
    }
}