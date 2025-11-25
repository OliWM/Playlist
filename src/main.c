#include <singly_linked_list.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRACK_TITLE_SIZE 60

#define PLAYLIST_IN_PATH "playlist.txt"
#define PLAYLIST_OUT_PATH "playlist-out.txt"
// To avoid unnecessary complexity, we fix the filenames instead of getting them
// through runtime parameters.

typedef char Data[TRACK_TITLE_SIZE];
Node *playlist;

/// Removes trailing newline from the line, if it exists.
/// Note: Some lines may not have a newline, e.g., last line in a file,
/// therefore we have to check for presence.
char *remove_newline_if_exists(char *line) {
  char *p = line;
  while (*p != '\0') { // NULL evaluates to false so not really necessary, could
                    // just say while(*p) I think
      if (*p == '\n') {
        *p = '\0'; //dereferencing. *p and line point to same place in memory so changing it here should change line too. Could have used index of line instead I guess
        break; //if somehow we had a line w. two newlines I guess we don't handle that.. But we put in the NULL so it should terminate there anyways, regardless of what comes after.
      }
    p++; //loops through each char in p slash in line
    }
  return line;
}

/// Reads lines from at `filename`, creates a node for each line and inserts
/// nodes to `list`.
Node **load_file(const char *filename, Node **list) {
  // Open the file and assign to stream `f`
  FILE *f = fopen(filename, "r");
  if (!f) { //fopen returns NULL if it cannot open. So if we cannot open the file, we return the error message and exit.
    perror(PLAYLIST_IN_PATH); //by some magic prints if no file exists or if we don't have permission
    exit(EXIT_FAILURE);
  }
  char line[TRACK_TITLE_SIZE]; //allocate local buffer. It's set to 60 which I guess should be enough for all titles. 

  while (
      // Read one line from the stream
      fgets(line, TRACK_TITLE_SIZE, f) //this is where line is populated
  ) {
    remove_newline_if_exists(line);

    auto new_node = (Node *)malloc(sizeof(Node)); //creates an independent node in the heap memory
    new_node->next = nullptr; //To make it the tail I guess?
    auto data = (Data *)malloc(sizeof(Data)); 
    new_node->data = data;

    // Copy line to `new_node` and append `new_node` to `list`
    strcpy((char *)new_node->data, line); //tells compiler the void pointer is a char *
    insert_at(list, list_len(*list), new_node); //functions coming from the stringly_linked_list.c file provided
  }
  fclose(f); //closes the file but the heap memory persists.
  return list;
}

/// Saves `list` contents to the file at `filename`.
void save_file(const char *filename, Node *list) {
  // Open file
  FILE *f = fopen(filename, "w");
  if (!f) {
    perror(PLAYLIST_OUT_PATH); //same error handling as above
    exit(EXIT_FAILURE);
  }

  // Move through the list and save the tracks to the file
  // Note: You have to cast the data to print the track to the file as follows:
  // `*(Data *)current->data`, which is the same as `(char *)current->data`.
  // We need this cast, because `data` is a pointer to everything (`void *`).
  auto current = playlist;
  while (current) { // we iterate as long as there are more lines
    fprintf(f, "%s\n", *(Data *)current->data); //add back newlines. Casting to data and dereferencing to get string
    current = current->next;
  }

  fclose(f);
}

void print_tracks(const Node *const playlist) {
  auto current = playlist;
  for (size_t i = 1; current; i++, current = current->next)
    printf("%2ld: %s\n", i, (char *)current->data);
}

int main() {
  load_file(PLAYLIST_IN_PATH, &playlist);
  puts("Loaded tracks:");
  print_tracks(playlist);

  // Deletion
  size_t node_index_to_del = 4;
  free(delete_at(&playlist, node_index_to_del)); //frees the malloc'd space in heap

  // Insertion
  Node node = {.data = "Tarkan – Şımarık 💋", .next = nullptr};
  insert_at(&playlist, 3, &node);

  save_file(PLAYLIST_OUT_PATH, playlist);
}