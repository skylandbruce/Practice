import java.util.HashMap;

public class Monad {
    protected HashMap cell;
    protected int index;

    protected String name;
    
	public Monad() {
		cell = new HashMap<>();
		index = 0;
	}
    public Monad(String name) {
		cell = new HashMap<>();
		index = 0;
        this.name=name;
	}
    public void set_dna(Dna dna) {
        for (int i=0; i<cell.size(); i++)
          ((Nucleus)cell.get(i)).set_dna(dna);
    }

    public void incubate_cell(Nucleus nucleus) {
        cell.put(nucleus.get_label().get_unique(),nucleus);
    }

    public void incubate_cell(HashMap cell_parts) {
        cell.putAll(cell_parts);
    }

/* 
    public boolean hasNext() {
        return (index >= 0) && (index < cell.size());
      }
    
    public Nucleus nextNucleus() {
        Nucleus nucleus = null;
        try {
            nucleus = (Nucleus)cell.get(index++);
        }
        catch (IndexOutOfBoundsException e) {
            return null;
        }
        return nucleus;
    }
 */
    public Nucleus get_nucleus(Label label){
        return (Nucleus)cell.get(label.get_unique());
    }

    public HashMap get_cell(){
        return cell;
    }

    // public Nucleus[] get_cell(Nucleus[] type){
    //     return (Nucleus[]) cell.toArray(type);
    // }

}