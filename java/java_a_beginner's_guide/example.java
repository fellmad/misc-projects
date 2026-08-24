class Example {
    public static void main(String args[]) {
        System.out.println("yo.");
        Fred fred = new Fred();
        fred.a_Fred_method();
    }
}

class Fred {
    public void a_Fred_method() {
        System.out.println("a fred method.");
    }
}