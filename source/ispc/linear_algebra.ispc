 export void VectorDotProd(
	uniform float out[], uniform const float vec_lhs[], uniform const float vec_rhs[], uniform const uint8 len){
	foreach (index = 0 ... len) {
        float lhs = vec_lhs[index];
        float rhs = vec_rhs[index];
        *out = reduce_add(lhs * rhs);
	}
 }

export void VectorCrossProdV3(
    uniform float vec_out[3], uniform const float vec_lhs[3], uniform const float vec_rhs[3]){
	foreach(index = 0 ... 3) {
		int index_a = ((index + 1 == 3) ? 0 : index + 1);
		int index_b = ((index == 0) ? 2 : index - 1);
		vec_out[index] = vec_lhs[index_a] * vec_rhs[index_b] - vec_lhs[index_b] * vec_rhs[index_a];
	}
}

export void VectorTransformV4(uniform const float mat_lhs[16], uniform float vec_rhs[4]){
    foreach(index = 0 ... 4) {
        vec_rhs[index] = (vec_rhs[0] * mat_lhs[index*4]) 
            + (vec_rhs[1] * mat_lhs[index*4 + 1]) 
            + (vec_rhs[2] * mat_lhs[index*4 + 2]) 
            + (vec_rhs[3] * mat_lhs[index*4 + 3]);
    }
}

export void BuildIdentity(uniform float mat_arg[], const uniform int dim)
{
	foreach(i = 0 ... dim, j = 0 ... dim) {
		if (i == j)
			mat_arg[i * dim + j] = 1;
		else
			mat_arg[i * dim + j] = 0;
	}
}

export void MatrixTranspose(
    uniform float mat_out[], uniform const float mat_arg[], uniform const uint8 row, uniform const uint8 col){
        foreach(i = 0 ... row, j = 0 ... col) {
		    mat_out[j * row + i] = mat_arg[i * col + j];
	}
}
