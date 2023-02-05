import java.util.HashMap;

import Record.*;

public class CopyObj {
    public static void main(String[] args) {
        
        Record record = new FlashRecord();
        Dna dna=new Dna(record);
        
        Obj obj=new Obj();
        obj.set_str("str_01");
        obj.set_int(1);

        dna.reserve_monad(obj,3);
        HashMap<Long,Nucleus> cell=dna.pull_monad(obj);
        for(Long key:cell.keySet()){
            Obj ob=(Obj)cell.get(key);
            Label label=ob.get_label();

            String str=String.format("name:%s, uinque:%d, attr1:%s, attr2:%d",
            label.get_name(),label.get_unique(),ob.get_str(),ob.get_int());
            System.out.println(str);
        }
        

        /*       
        Obj obj=new Obj();
        Label label=obj.get_label();
        obj.set_str("str_01");
        obj.set_int(1);
 
        dna.push_ob(obj);
        Obj obj_pull=(Obj)dna.pull_obj(label);  
        System.out.printf("get confirm name:%s, key:%s\n",obj_pull.get_label().get_name(),obj_pull.get_label().get_key());
        String str=String.format("attr_str:%s, attr_int:%d", obj_pull.get_str(), obj_pull.get_int());
        System.out.println(str);
        
        obj=new Obj();
        label=obj.get_label();
        obj.set_str("str_02");
        obj.set_int(2);

        dna.push_ob(obj);
        obj_pull=(Obj)dna.pull_obj(label);
        System.out.printf("get confirm name:%s, key:%s\n",obj_pull.get_label().get_name(),obj_pull.get_label().get_key());
        str=String.format("attr_str:%s, attr_int:%d", obj_pull.get_str(), obj_pull.get_int());
        System.out.println(str);
 */
    }        
}    

