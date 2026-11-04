.PHONY: all configure build flash clean

# Defaults to the Debug preset, override with `make PRESET=Release ...`
PRESET ?= Debug
# Colour theme: white (dash-white-bg) or black (dash-black-bg), e.g. `make THEME=black flash`
THEME ?= white
BUILD_DIR = build/$(PRESET)-$(THEME)
CMAKE := $(shell which cmake)

all build: $(BUILD_DIR)/CMakeCache.txt
	$(CMAKE) --build $(BUILD_DIR)

$(BUILD_DIR)/CMakeCache.txt:
	$(CMAKE) --preset $(PRESET) -B $(BUILD_DIR) -DDASH_THEME=dash-$(THEME)-bg

flash: $(BUILD_DIR)/CMakeCache.txt
	$(CMAKE) --build $(BUILD_DIR) --target flash

clean:
	rm -rf build
