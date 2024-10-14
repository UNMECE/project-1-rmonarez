#include <iostream>
#include <vector>
#include <cmath> 

struct Capacitor {
    std::vector<double> time;    
    std::vector<double> voltage; 
    std::vector<double> current; 
    double C;                    
};

Capacitor init_capacitor(double C, int num_timesteps) {
    Capacitor cap;
    cap.C = C;
    cap.time.resize(num_timesteps);
    cap.voltage.resize(num_timesteps);
    cap.current.resize(num_timesteps);
    return cap;
}

void simulate_constant_current(Capacitor& cap, double I_const, double dt, int num_timesteps) {
    cap.voltage[0] = 0.0;
    cap.current[0] = I_const;
    
    for (int t = 1; t < num_timesteps; ++t) {
        cap.time[t] = t * dt;
        cap.voltage[t] = cap.voltage[t-1] + cap.current[t-1] * dt / cap.C;
        cap.current[t] = I_const;
        
        if (t % 200 == 0) {
            std::cout << "Time: " << cap.time[t] << " s, Voltage (Constant Current): " 
                      << cap.voltage[t] << " V, Current: " << cap.current[t] << " A" << std::endl;
        }
    }
}

void simulate_constant_voltage(Capacitor& cap, double V0, double R, double dt, int num_timesteps) {
    cap.voltage[0] = 0.0;
    cap.current[0] = V0 / R;
    
    for (int t = 1; t < num_timesteps; ++t) {
        cap.time[t] = t * dt;
        cap.current[t] = cap.current[t-1] - cap.current[t-1] * dt / (R * cap.C);
        cap.voltage[t] = V0 - cap.current[t] * R;
        
        if (t % 200 == 0) {
            std::cout << "Time: " << cap.time[t] << " s, Voltage (Constant Voltage): " 
                      << cap.voltage[t] << " V, Current: " << cap.current[t] << " A" << std::endl;
        }
    }
}

int main() {
    double dt = 1e-10;                  
    double final_time = 5e-6;           
    int num_timesteps = final_time / dt; 
    double C = 100e-12;              
    double R = 1e3;                  
    double I_const = 1e-2;             
    double V0 = 10.0;                   

    Capacitor cap = init_capacitor(C, num_timesteps);

    std::cout << "Constant Current Charging:" << std::endl;
    simulate_constant_current(cap, I_const, dt, num_timesteps);

    std::cout << "\nConstant Voltage Charging:" << std::endl;
    simulate_constant_voltage(cap, V0, R, dt, num_timesteps);

    return 0;
}
