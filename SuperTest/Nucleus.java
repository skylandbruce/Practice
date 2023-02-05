import java.util.HashMap;
import util.UniqueGenerator;

public abstract class Nucleus {
    protected Label label;
    private HashMap rna;
    private Dna dna;
    private String key;
    private UniqueGenerator unique;
    Nucleus(){
        label=set_label();
        rna=new HashMap<>();
        label.set_unique(unique.instance().getUniqueNumber());
    }
    protected abstract Nucleus get_instance();
    protected abstract Label set_label();

    /**
     * Nucleus를 통한 개별 Persistance 접근을 위해
     * @param dna
     */
    public void set_dna(Dna dna){
        this.dna=dna;
    }
    /*
    public void set_unique(long unique){
        label.set_unique(unique);
    }
     */
    public Label get_label(){
        return label;
    }

    /**
     * Object 의 attribute 를 등록 하고, 참조
     * @param fieldName
     * @param initValue
     */
    protected void regist_attribute(String fieldName, Object initValue) {
		rna.put(fieldName, initValue);
	}
	
	protected void set_value(String fieldName, Object value){
		rna.put(fieldName,value);
	}
	protected Object get_value(String fieldName) {
	    return rna.get(fieldName);
	}

    public HashMap self_replication(int dump_size){
        HashMap cell_parts=new HashMap<Long,Nucleus>();
        for(int i=0; i<dump_size; i++){
            Nucleus obj=this.get_instance();
            cell_parts.put(obj.get_label().get_unique(),obj);
        }
        return cell_parts;
    }

 

}
