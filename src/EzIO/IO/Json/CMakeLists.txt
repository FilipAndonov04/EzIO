target_sources(ezio PRIVATE
    JsonSerializer.h
    JsonSerializer.cpp
    JsonDeserializer.h
    JsonDeserializer.cpp
    JsonConstants.h
)

add_subdirectory(Tokenizer)