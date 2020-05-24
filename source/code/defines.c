
// alternative for c_trace
var ent_trace(ENTITY *ent, VECTOR *from, VECTOR *to, var mode)
{
	if(!ent)
	{
		diag("\nERROR! Can't perform trace.. My entity doesn't exist!");
		return -1;
	}
	my = ent;
	var distance = c_trace(from, to, TRACE_FLAGS | mode);
	my = NULL;
	return distance;
}