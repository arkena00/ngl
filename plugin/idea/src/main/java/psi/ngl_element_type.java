package psi;

import com.intellij.psi.tree.IElementType;
import ngl.ngl;
import org.jetbrains.annotations.*;

public class ngl_element_type extends IElementType {
    public ngl_element_type(@NotNull @NonNls String debugName) {
        super(debugName, ngl.INSTANCE);
    }
}