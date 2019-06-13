package ngl;

import com.intellij.openapi.fileTypes.*;
import org.jetbrains.annotations.NotNull;

public class ngl_file_type_factory extends FileTypeFactory {
    @Override
    public void createFileTypes(@NotNull FileTypeConsumer fileTypeConsumer) {
        fileTypeConsumer.consume(ngl_file_type.INSTANCE);
    }
}