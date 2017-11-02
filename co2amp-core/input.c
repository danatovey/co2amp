#include  "co2amp.h"


void ReadCommandLine(int argc, char **argv)
{
    int i;

    // ------- INITIAL PULSE -------
    from_file = 0;          // 1: use input field from files 'field_in_re.dat' and 'field_in_im.dat'
    E0 = 1;                 // Initial pulse energy, J
    r0 = 0.01;              // Initial beam radius (hwhm), m
    tau0 = 5e-12;           // Initial pulse half-width (fwhm), s
    vc = 2.8306225e13;      // Carrying frequency, Hz; default 10P(20) line
    t_inj = 0;              // Injection moment, us
    n_pulses = 1;           // Number of pulses in the train
    Dt_train = 0.1e-6;      // Delay between pulses in the train, s (only for n_pulses > 1)
    // ------- OPTICS, GEOMETRY -------
    noprop = false;         // Skip propagation calculations
    // ------- PUMPING -------
    strcpy(pumping, "discharge"); // Pumping type (discharge or optical)
    Vd = 0.0085;            // Ddischarge volume, m^3
    D = 0.085;              // Ddistance between electrodes, m
    pump_wl = 2.79e-6;      // Wavelength of optical pumping, m
    pump_sigma = 1e-25;     // Absorption cross-section for optical pumping, m^2
    pump_fluence = 1e4;     // Fluence of optical pumping, J/m^2
    // -------- GAS MIXTURE --------
    p_626 = 0.5;            // 16O-12C-16O pressure, bar
    p_628 = 0;              // 16O-12C-18O pressure, bar
    p_828 = 0;              // 18O-12C-18O pressure, bar
    p_636 = 0;              // 16O-13C-16O pressure, bar
    p_638 = 0;              // 16O-13C-18O pressure, bar
    p_838 = 0;              // 18O-13C-18O pressure, bar
    p_N2 = 0.5;             // N2 pressure, bar
    p_He = 2;               // He pressure, bar
    T0 = 300;               // Initial gas temperature, K
    // ------- CALCULATION NET -------
    x0 = 64;
    n0 = 64;
    t_pulse_lim = 80e-12;   // Pulse time calculation limit, s
    t_pulse_shift = 15e-12; // Pulse shift from 0, s
    Dt_pump = 2.0e-9;       // Time net step for pumping/relaxation calculations, s // fixed!
    // ---------- DEBUGGING ----------
    debug_level = 0;        // No debugging info output by default
    bands = 7;              // All bands (1 for regular + 2 for hot + 4 for sequence)

    //Read command line
    char debug_str[1024];
    strcpy(debug_str, "Command line: ");
    for (i=1; i<argc; i++){
        // debug string
        strcat(debug_str, argv[i]);
        strcat(debug_str, " ");
        // ------- INITIAL PULSE -------
        if (!strcmp(argv[i], "-from_file"))
            from_file = atoi(argv[i+1]);
        if (!strcmp(argv[i], "-E0"))
            E0 = atof(argv[i+1]);
        if (!strcmp(argv[i], "-r0"))
            r0 = atof(argv[i+1])*1e-2;      // cm->m
        if (!strcmp(argv[i], "-tau0"))
            tau0 = atof(argv[i+1])*1e-12;   // ps->s
        if (!strcmp(argv[i], "-vc"))
            vc = atof(argv[i+1])*1e12;      // THz->Hz;
        if (!strcmp(argv[i], "-t_inj"))
            t_inj = atof(argv[i+1])*1e-6;   // us->s
        if (!strcmp(argv[i], "-n_pulses"))
            n_pulses = atoi(argv[i+1]);
        if (!strcmp(argv[i], "-Dt_train"))
            Dt_train = atof(argv[i+1])*1e-6; // us->s
        // ------- LAYOUT -------
        if (!strcmp(argv[i], "-noprop"))
            noprop = true;
        // ------- PUMPING -------
        if (!strcmp(argv[i], "-pumping"))
            strcpy(pumping, argv[i+1]);
        if (!strcmp(argv[i], "-Vd"))
            Vd = atof(argv[i+1])*1e-6;      // cm^3->m^3
        if (!strcmp(argv[i], "-D"))
            D = atof(argv[i+1])*1e-2;       // cm->m
        if (!strcmp(argv[i], "-pump_wl"))
            pump_wl = atof(argv[i+1])*1e-6;   // um -> m
        if (!strcmp(argv[i], "-pump_sigma"))
            pump_sigma = atof(argv[i+1])*1e-4;   // cm^2 -> m^2
        if (!strcmp(argv[i], "-pump_fluence"))
            pump_fluence = atof(argv[i+1])*1e4;   // J/cm^2 -> J/m^2
        // ------- GAS MIXTURE -------
        if (!strcmp(argv[i], "-p_626"))
            p_626 = atof(argv[i+1]);
        if (!strcmp(argv[i], "-p_628"))
            p_628 = atof(argv[i+1]);
        if (!strcmp(argv[i], "-p_828"))
            p_828 = atof(argv[i+1]);
        if (!strcmp(argv[i], "-p_636"))
            p_636 = atof(argv[i+1]);
        if (!strcmp(argv[i], "-p_638"))
            p_638 = atof(argv[i+1]);
        if (!strcmp(argv[i], "-p_838"))
            p_838 = atof(argv[i+1]);
        p_CO2 = p_626+p_628+p_828+p_636+p_638+p_838; // Total CO2 pressure, bar
        if (!strcmp(argv[i], "-p_N2"))
            p_N2 = atof(argv[i+1]);
        if (!strcmp(argv[i], "-p_He"))
            p_He = atof(argv[i+1]);
        if (!strcmp(argv[i], "-T0"))
            T0 = atof(argv[i+1]);
        // ------- CALCULATION NET -------
        if (!strcmp(argv[i], "-x0"))
            x0 = atoi(argv[i+1]);
        if (!strcmp(argv[i], "-n0"))
            n0 = atoi(argv[i+1]);
        if (!strcmp(argv[i], "-t_pulse_lim"))
            t_pulse_lim = atof(argv[i+1])*1e-12;   // ps->s
        if (!strcmp(argv[i], "-t_pulse_shift"))
            t_pulse_shift = atof(argv[i+1])*1e-12; // ps->s
        // --------- DEBUGGING ---------
        if (!strcmp(argv[i], "-debug"))
            debug_level = atoi(argv[i+1]);
        if (!strcmp(argv[i], "-bands"))
            bands = atoi(argv[i+1]);
    }
    Debug(2, debug_str);
}


void ConstantsInit(void)
{
    // Constants
    c = 2.99792458e8; // m/s
    h = 6.626069e-34; // J*s

    double Dt = t_pulse_lim/(n0-1); // pulse time step, s
    double Dv = 1.0/(Dt*n0);        // frequency step, Hz
    v_min = vc - Dv*(n0-1)/2;
    v_max = vc + Dv*(n0-1)/2;

    // Count number of data points in the discharge profile
    if(!strcmp(pumping, "discharge")){
        int size;
        char *str, *file_str;
        n_discharge_points = 0;
        FILE *file;
        file = fopen("discharge.txt", "r");
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        rewind(file);
        file_str = malloc(size+1);
        fread(file_str, size, 1, file);
        file_str[size] = '\0'; // string terminating character
        str = strtok(file_str,"\n");
        while(str != NULL){
            n_discharge_points ++;
            str = strtok(NULL,"\n");
        }
        free(file_str);
        fclose(file);
    }

    // Optical layout: count number of components and active medium sections
    int size;
    char *str, *file_str;
    n_components = 0;
    n_amsections = 0;
    FILE *file;
    file = fopen("optics_components.txt", "r");
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    file_str = malloc(size+1);
    fread(file_str, size, 1, file);
    file_str[size] = '\0'; // string terminating character
    str = strtok (file_str," \t\n\r");
    while(str != NULL){
        if(!strcmp(str, "AM") || !strcmp(str, "PROBE") || !strcmp(str, "MASK") || !strcmp(str, "ATTENUATOR")
                || !strcmp(str, "ABSORBER") || !strcmp(str, "LENS") || !strcmp(str, "WINDOW") || !strcmp(str, "STRETCHER")
                || !strcmp(str, "BANDPASS") || !strcmp(str, "APODIZER") || !strcmp(str, "AIR"))
            n_components ++;
        if(!strcmp(str, "AM"))
            n_amsections ++;
        str = strtok(NULL," \t\n\r");
    }
    free(file_str);
    fclose(file);

    // Optical layout: count number of propagations
    n_propagations = 0;
    file = fopen("optics_layout.txt", "r");
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    file_str = malloc(size+1);
    fread(file_str, size, 1, file);
    file_str[size] = '\0'; // string terminating character
    str = strtok (file_str," -\t\n\r");
    while(str != NULL){
        n_propagations ++;
        str = strtok(NULL," -\t\n\r");
    }
    n_propagations = (n_propagations+1)/2;
    free(file_str);
    fclose(file);

    printf("components: %d; layout: %d; a.m. sections: %d; pulses: %d\n",n_components, n_propagations, n_amsections, n_pulses);
    fflush(stdout);

}


void ArraysInit(void)
{
    int i, k, K;

    int N_symm = 0;  //Number of symmetric CO2 molecules
    int N_asymm = 0; // --''-- asymmetric --''--

    if(p_626>0)
        N_symm++;
    if(p_628>0)
        N_asymm++;
    if(p_828>0)
        N_symm++;
    if(p_636>0)
        N_symm++;
    if(p_638>0)
        N_asymm++;
    if(p_838>0)
        N_symm++;

    // Read discharge profile
    if(!strcmp(pumping, "discharge")){
        int size;
        char *str, *file_str;
        FILE *file;
        file = fopen("discharge.txt", "r");
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        rewind(file);
        file_str = malloc(size+1);
        fread(file_str, size, 1, file);
        file_str[size] = '\0'; // string terminating character
        str = strtok(file_str," \t\n\r");
        i=0;
        while(str != NULL){
            discharge[0][i] = atof(str)*1e-6; // time, us->s
            str = strtok(NULL," \t\n\r");
            discharge[1][i] = atof(str);      // Current, A
            str = strtok(NULL," \t\n\r");
            discharge[2][i] = atof(str);      // Voltage, V
            str = strtok(NULL," \t\n\r");
            i++;
        }
        free(file_str);
        fclose(file);
        if(debug_level>=2){
            printf("\nDISCHARGE PROFILE:\n");
            printf("t, us\tI, A\tU, V\n");
            for(i=0; i<n_discharge_points; i++)
                printf("%f\t%f\t%f\n", discharge[0][i]*1e6, discharge[1][i], discharge[2][i]);
            fflush(stdout);
        }
    }

    // Read component data from 'optics_components.txt' file
    int size;
    char *str, *file_str, id[64];
    FILE *file;
    file = fopen("optics_components.txt", "r");
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    file_str = malloc(size+1);
    fread(file_str, size, 1, file);
    file_str[size] = '\0'; // string terminating character
    str = strtok(file_str," \t\n\r");
    K = 0; //component number
    while(str != NULL){
        if(!strcmp(str, "AM") || !strcmp(str, "PROBE") || !strcmp(str, "MASK") || !strcmp(str, "ATTENUATOR")
                || !strcmp(str, "ABSORBER") || !strcmp(str, "LENS") || !strcmp(str, "WINDOW") || !strcmp(str, "STRETCHER")
                || !strcmp(str, "BANDPASS") || !strcmp(str, "APODIZER") || !strcmp(str, "AIR")){
            strcpy(component_id[K], id);
            strcpy(component_type[K], str);
            component_Dr[K] = atof(strtok(NULL," \t\n\r")) / (x0-1) * 1e-2; // cm -> m
            if(noprop) // no propagation calculations
                component_Dr[K] = component_Dr[0];
            strcpy(component_param1[K], "");
            strcpy(component_param2[K], "");
            if(!strcmp(str, "AM") || !strcmp(str, "MASK") || !strcmp(str, "ATTENUATOR") || !strcmp(str, "ABSORBER")
                    || !strcmp(str, "LENS") || !strcmp(str, "WINDOW") || !strcmp(str, "STRETCHER") || !strcmp(str, "BANDPASS")
                    || !strcmp(str, "APODIZER") || !strcmp(str, "AIR"))
                strcpy(component_param1[K], strtok(NULL," \t\n\r")); // 1st parameter
            if(!strcmp(str, "WINDOW") || !strcmp(str, "BANDPASS") || !strcmp(str, "AIR"))
                strcpy(component_param2[K], strtok(NULL," \t\n\r")); // 2nd parameter
            K ++;
        }
        strcpy(id, str);
        str = strtok(NULL," \t\n\r");
    }
    free(file_str);
    fclose(file);

    printf("\nCOMPONENTS (distances in cm):\n");
    printf("[id]\t\[type]\t\[field]\t[param1]\t[param2]\n");
    for(K=0; K<n_components; K++){
        // output: distances in cm
        printf("%s\t%s\t%f\t%s\t%s\n",component_id[K], component_type[K], component_Dr[K]*(x0-1)*100, component_param1[K], component_param2[K]);
        fflush(stdout);
    }

    // Read component data from 'optics_layout.txt' file
    file = fopen("optics_layout.txt", "r");
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    file_str = malloc(size+1);
    fread(file_str, size, 1, file);
    file_str[size] = '\0'; // string terminating character
    str = strtok (file_str," -\t\n\r");
    double t = t_inj;
    for(k=0; k<n_propagations; k++){
        layout_component[k] = -1; // flag to show that component id is not found
        for(i=0; i<n_components; i++){
            if(!strcmp(str, component_id[i]))
                layout_component[k] = i;
        }
        layout_time[k] = t;
        str = strtok(NULL," -\t\n\r");
        if(str != NULL)
            layout_distance[k] = atof(str) * 1e-2; // cm -> m
        else
            layout_distance[k] = 0;
        t += layout_distance[k] / c; // t[s]
        str = strtok(NULL," -\t\n\r");
    }
    free(file_str);
    fclose(file);

    int flag_error = 0;
    printf("\nLAYOUT:\n");
    for(k=0; k<n_propagations; k++){
        if(k != 0)
            printf("-");
        if(layout_component[k] != -1)
            printf("%s", component_id[layout_component[k]]);
        else{
            printf("[?]");
            flag_error = 1;
        }
        if(k != n_propagations-1)
            printf("-%.1f", layout_distance[k]*1e2); // m->cm
    }
    printf("\n");
    fflush(stdout);

    if(flag_error){
        printf("\nError in optical layout :(\nAbnormal program termination\n");
        FreeMemory();
        abort();
    }
}


void IntensityNormalization(void) // Field amplitude adjustment (to match initial pulse energy)
{
    int pulse, x, n;
    double Energy, af;
    double Dr = component_Dr[layout_component[0]];
    double Dt = t_pulse_lim/(n0-1);

    for(pulse=0; pulse<=n_pulses-1; pulse++){
        Energy = 0;
        for(n=0; n<n0-1; n++){
            for(x=0; x<x0-1; x++)
                Energy += 2.0 * h * vc * pow(cabs(E[pulse][x][n]+E[pulse][x][n+1]+E[pulse][x+1][n]+E[pulse][x+1][n+1])/4, 2) * 2*M_PI*(Dr*x+Dr/2)*Dr * Dt; // J
            }

        af = sqrt(E0/Energy);
        for(n=0; n<n0; n++){
            for(x=0; x<x0; x++)
                E[pulse][x][n] *= af;
        }
    }
}


void InitializeE()
{
    int pulse, x, n;
    FILE *file;

    double Dr = component_Dr[layout_component[0]];
    double Dt = t_pulse_lim/(n0-1);

    if(!from_file){
        for(pulse=0; pulse<n_pulses; pulse++){
            for(x=0; x<x0; x++){
                for(n=0; n<n0; n++)
                    E[pulse][x][n] = field(Dr*x, Dt*n);
            }
        }
        IntensityNormalization();
    }
    else{
        file = fopen("field_in.bin", "rb");
        for(pulse=0; pulse<n_pulses; pulse++){
            for(x=0; x<x0; x++)
                fread(E[pulse][x], sizeof(double complex)*n0, 1, file);
        }
        fclose(file);
    }
}


double complex field(double r, double t)
{
    double xx;
    xx = tau0/sqrt(log(2.0)*2.0);	//(fwhm -> half-width @ 1/e^2)
    double pulse = exp(-pow((t-t_pulse_shift)/xx, 2));
    xx = r0/sqrt(log(2.0)/2.0);   //(hwhm -> half-width @ 1/e^2)
    double beam = exp(-pow(r/xx, 2.0));
    return pulse*beam;
}
