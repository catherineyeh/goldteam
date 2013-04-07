#ifndef _KERN_HASH_H
#define _KERN_HASH_H

struct hash {
  unsigned size;
  int* table;
};

struct hash* hash_create(int size) {
  struct hash* h;
  /*
  h->size = size;
  h->table = (int*)calloc(sizeof(int)*size);
  */
  return h;
}

void hash_add(struct hash *h, int val) {
  int val_hash = val % h->size;
  h->table[val_hash] = val;
}

//struct hash* test_h;
//test_h = hash_create(100);

#endif /* _KERN_HASH_H */
