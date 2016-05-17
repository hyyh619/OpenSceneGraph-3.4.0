char volume_accumulateSamples_standard_tf_frag[] = "#version 110\n"
                                                   "\n"
                                                   "uniform sampler3D volumeTexture;\n"
                                                   "uniform sampler1D tfTexture;\n"
                                                   "\n"
                                                   "uniform float tfScale;\n"
                                                   "uniform float tfOffset;\n"
                                                   "uniform float TransparencyValue;\n"
                                                   "uniform float AlphaFuncValue;\n"
                                                   "\n"
                                                   "vec4 accumulateSamples(vec4 fragColor, vec3 ts, vec3 te, vec3 dt, float scale, float cutoff, int num_iterations)\n"
                                                   "{\n"
                                                   "    vec3 texcoord = te.xyz;\n"
                                                   "\n"
                                                   "    float transmittance = 1.0;\n"
                                                   "    float t_cutoff = 1.0-cutoff;\n"
                                                   "    while(num_iterations>0 && transmittance>=t_cutoff)\n"
                                                   "    {\n"
                                                   "        float a = texture3D( volumeTexture, texcoord).a;\n"
                                                   "        float v = a * tfScale + tfOffset;\n"
                                                   "        vec4 color = texture1D( tfTexture, v);\n"
                                                   "\n"
                                                   "        if (a>=AlphaFuncValue)\n"
                                                   "        {\n"
                                                   "            float ca = clamp(color.a*TransparencyValue, 0.0, 1.0);\n"
                                                   "            float new_transmitance = transmittance*pow(1.0-ca, scale);\n"
                                                   "            float r = transmittance-new_transmitance;\n"
                                                   "            fragColor.rgb += color.rgb*r;\n"
                                                   "            transmittance = new_transmitance;\n"
                                                   "        }\n"
                                                   "\n"
                                                   "        texcoord += dt;\n"
                                                   "\n"
                                                   "        --num_iterations;\n"
                                                   "    }\n"
                                                   "\n"
                                                   "    fragColor.a = clamp(1.0-transmittance, 0.0, 1.0);\n"
                                                   "    if (num_iterations>0) fragColor.a = 1.0;\n"
                                                   "\n"
                                                   "    return fragColor;\n"
                                                   "}\n"
                                                   "\n";