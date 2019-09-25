public interface BinarySearchTreeADT {
    /* Offset Binary Search Tree ADT */

    public DictEntry find (Position key);
                   /* Returns the DictEntry storing the given key, if the key 
		      is stored in the tree. Returns null otherwise.        */

    public void insert (DictEntry data) throws BSTException;
                  /* Inserts the given data in the tree if no data item with
		     the same key is already there. If a node already stores
		     the same key, the algorithm throws a BSTException. */

    public void remove (Position key) throws BSTException;
                   /* Removes the data item with the given key, if the key 
		      is stored in the tree. Throws a BSTException otherwise.*/

    public DictEntry successor (Position key);
                 /* Returns the DictEntry with the smallest key larger than
		    the given one (note that the tree does not need to store
		    a node with the given key). Returns null if the given word
		    key has no successor. */

    public DictEntry predecessor (Position key);
                 /* Returns the DictEntry with the largest key smaller than
		    the given one (note that the tree does not need to store
		    a node with the given key). Returns null if the given word
		    key has no predecessor. */

    public DictEntry smallest();
                 /* Returns the DictEntry with the smallest key. Returns null
		    if the tree is empty. */

    public DictEntry largest();
                 /* Returns the DictEntry with the largest key. Returns null
		    if the tree is empty. */

}
		


