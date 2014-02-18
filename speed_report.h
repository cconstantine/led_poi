class SpeedReport {
public:
  SpeedReport();
  void tick();

private:
  unsigned long last_millis;
  unsigned long ticks;
};



