#include <stdio.h>
#include <windows.h>
#include <string.h>

// Function to create a directory and all necessary parent directories
int create_directory(const char *path) {
    // Check if the folder already exists
    DWORD dwAttrib = GetFileAttributes(path);

    // If the folder exists, return 0
    if (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
        printf("Directory '%s' already exists.\n", path);
        return 0;  // Folder already exists
    }

    // Try to create the folder
    if (CreateDirectory(path, NULL)) {
        printf("Directory '%s' created successfully!\n", path);
        return 1;  // Folder created successfully
    }

    // Get the last error code
    DWORD error_code = GetLastError();

    // Output more detailed error information
    printf("Error creating directory '%s': %lu\n", path, error_code);

    return -1;  // Error creating the folder
}

int main(int argc, char *argv[]) {
    // Check if the user provided a path
    if (argc < 2) {
        printf("Please provide the base path as an argument.\n");
        return 1;  // Exit the program if no path was provided
    }

    // Get the base path where the folders will be created
    const char *base_path = argv[1];  // The path specified by the user

    // List of main folders
    const char *main_folders[] = {
            "Backups",
            "Documents",
            "Media",
            "Program Files",
            "Program Files (x86)",
            "Projects",
            "Sundry"
    };

    // Create the main folders
    for (size_t i = 0; i < sizeof(main_folders) / sizeof(main_folders[0]); i++) {
        // Build the full path for each main folder
        char folder_path[512];
        snprintf(folder_path, sizeof(folder_path), "%s\\%s", base_path, main_folders[i]);

        // Create the folder
        create_directory(folder_path);
    }

    // If the Documents folder was successfully created, create the subfolders
    char documents_path[512];
    snprintf(documents_path, sizeof(documents_path), "%s\\Documents", base_path);

    if (GetFileAttributes(documents_path) != INVALID_FILE_ATTRIBUTES) {
        const char *documents_folders[] = {"Finance", "Job", "Personal", "Studies"};
        for (size_t i = 0; i < sizeof(documents_folders) / sizeof(documents_folders[0]); i++) {
            char folder_path[512];
            snprintf(folder_path, sizeof(folder_path), "%s\\%s\\%s", base_path, "Documents", documents_folders[i]);
            create_directory(folder_path);
        }
    }

    // If the Media folder was successfully created, create the subfolders
    char media_path[512];
    snprintf(media_path, sizeof(media_path), "%s\\Media", base_path);

    if (GetFileAttributes(media_path) != INVALID_FILE_ATTRIBUTES) {
        const char *media_folders[] = {"Music", "Photos", "Video"};
        for (size_t i = 0; i < sizeof(media_folders) / sizeof(media_folders[0]); i++) {
            char folder_path[512];
            snprintf(folder_path, sizeof(folder_path), "%s\\%s\\%s", base_path, "Media", media_folders[i]);
            create_directory(folder_path);
        }
    }

    return 0;
}