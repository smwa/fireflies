class Clock
{
    public:
        Clock() {
            this->set_time(0);
        };
        int get_time();
        void set_time(int);
    private:
        int time;
};
