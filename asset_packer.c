#include <engine.h>

#ifndef PACK_FOLDER
#define PACK_FOLDER "include/packed/"
#endif // PACK_FOLDER

#ifndef ASSET_FOLDER
#define ASSET_FOLDER "resources/"
#endif // ASSET_FOLDER

bool pack_assets(void) {
	if (!DirectoryExists(PACK_FOLDER)) {
		log_info("Creating pack folder: %s", PACK_FOLDER);
		if (MakeDirectory(PACK_FOLDER) != 0) {
			log_error("Failed to create pack folder: %s", PACK_FOLDER);
			return false;
		}
	}

	FilePathList gfx_list = LoadDirectoryFiles(ASSET_FOLDER "gfx/");

	for (int i = 0; i < gfx_list.count; ++i) {
		const char* filepath = gfx_list.paths[i];
		if (IsFileExtension(filepath, ".png")) {
			log_info("Packing PNG: %s", filepath);
			int data_size = -1;
			const char* data = LoadFileData(filepath, &data_size);

			const char* basename = GetFileName(filepath);
			char* packed_filepath = TextFormat("%s%s.h", PACK_FOLDER, basename);

			if (data_size == -1) {
				log_error("Failed to read file: %s", filepath);
				return false;
			}

			if (!ExportDataAsCode(data, data_size, packed_filepath)) {
				log_error("Failed to export data as code: %s to %s", filepath, packed_filepath);
				return false;
			}

			UnloadFileData(data);

			log_info("		- Data size: %d bytes", data_size);
		}
	}
}