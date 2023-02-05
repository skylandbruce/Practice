public class Obj extends Nucleus{
    Obj(){
        super();
        /**
         * Object의 attribute를 Entity에 등록한다.
         */
        regist_attribute("attr_str_01","str");
        regist_attribute("attr_int_02",1);
    }
    protected Label set_label(){
        return new Label("Ob");
    }
    
    protected Nucleus get_instance(){
        //System.out.println("Obj Instance생성");
        Nucleus nucleus=(Nucleus)new Obj();
        return nucleus;
    }

    public void set_str(String value){
		set_value("field01",value);
	}
	public String get_str(){
		return (String)get_value("attr_str_01");
	}

	public void set_int(int value){
		set_value("field02",value);
	}
	public int get_int(){
		return (int) get_value("attr_int_02");
	}

}
