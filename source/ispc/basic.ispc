export void AddForeach(
    uniform float out[], uniform const float in_lhs[], uniform const float in_rhs[], uniform const uint8 len){
        foreach(index = 0 ... len)
    {
        out[index] = in_lhs[index] + in_rhs[index];
    }
}
export void SubForeach(
    uniform float out[], uniform const float in_lhs[], uniform const float in_rhs[], uniform const uint8 len){
        foreach(index = 0 ... len)
    {
        out[index] = in_lhs[index] - in_rhs[index];
    }
}
export void MulForeach(
    uniform float out[], uniform const float in_lhs[], uniform const float in_rhs[], uniform const uint8 len){
        foreach(index = 0 ... len)
    {
        out[index] = in_lhs[index] * in_rhs[index];
    }
}
export void DivForeach(
    uniform float out[], uniform const float in_lhs[], uniform const float in_rhs[], uniform const uint8 len){
            foreach(index = 0 ... len)
    {
        out[index] = in_lhs[index] / in_rhs[index];
    }
}
export void PowForeach(
    uniform float out[], uniform const float in_lhs[], uniform const float in_rhs[], uniform const uint8 len){
            foreach(index = 0 ... len)
    {
        out[index] = pow(in_lhs[index], in_rhs[index]);
    }
}
export void AbsForeach(
    uniform float out[], uniform const float in_arg[],  uniform const uint8 len){
            foreach(index = 0 ... len)
    {
        out[index] = abs(in_arg[index]);
    }
}
export void SqrtForeach(
    uniform float out[], uniform const float in_arg[],  uniform const uint8 len){
            foreach(index = 0 ... len)
    {
        out[index] = sqrt(in_arg[index]);
    }
}
export void NegForeach(
    uniform float out[], uniform const float in_arg[],  uniform const uint8 len){
            foreach(index = 0 ... len)
    {
        out[index] = -in_arg[index];
    }
}
