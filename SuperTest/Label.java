public class Label {
    private String name="";
    private long unique=0;
    private String key="";
    Label(String name){
        this.name=name;
        //System.out.println("Label생성");
    }
    
    public void set_unique(long unique){
        this.unique=unique;
    }

    public long get_unique(){
        return unique;
    }
    public String get_name(){
        return name;
    }
    public String get_key(){
        key=name+"_"+String.valueOf(unique);
        return key;
    }
}
