import java.util.HashMap;
import Record.Record;

public class Dna {
    private HashMap organ;
    private Monad monad;
    private Record record;

    Dna(Record record){
        organ=new HashMap<String, Monad>();
        this.record=record;    
    }
    public void push_obj(Nucleus nucleus){
        monad=(organ.containsKey(nucleus.get_label().get_name()))?(Monad)organ.get(nucleus.get_label().get_name()):new Monad();
        monad.incubate_cell(nucleus);
        // nucleus.set_dna(this);
        // nucleus.get_label().set_unique(unique.instance().getUniqueNumber());
        // //System.out.printf("push organ -name:%s, key:%s\n",nucleus.get_name(),nucleus.get_key());
        // organ.put(nucleus.get_label(), nucleus);
    }

    public Nucleus pull_obj(Label label){
        // return (Nucleus)organ.get(label);
        if(organ.containsKey(label.get_name())==false)
            return null;
        monad=(Monad)organ.get(label.get_name());
        return monad.get_nucleus(label);
    }

    public void reserve_monad(Nucleus seed,int dump_size){
        monad=(organ.containsKey(seed.get_label().get_name()))? (Monad)organ.get(seed.get_label().get_name()):new Monad();
        HashMap cell_parts=seed.self_replication(dump_size);        
        //monad.incubate_cell(cell_parts);
        organ.put(seed.get_label().get_name(), monad);
    }

    public void push_monad(Nucleus seed){
        monad=(organ.containsKey(seed.get_label().get_name()))? (Monad)organ.get(seed.get_label().get_name()):new Monad();
        HashMap cell_parts=seed.self_replication(dump_size);        
        monad.incubate_cell(cell_parts);
        organ.put(seed.get_label().get_name(), monad);
    }
    
    public HashMap pull_monad(Nucleus seed){
        if(organ.containsKey(seed.get_label().get_name())==false)
            return null;
        monad=(Monad)organ.get(seed.get_label().get_name());
        return monad.get_cell();
    }

}
