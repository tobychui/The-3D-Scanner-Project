import meshlabxml as mlx
def pc2stl(file_in = "input.asc", file_out = 'out.stl'):
	proj = mlx.FilterScript(file_in = file_in, file_out = file_out, ml_version='2016.12')
	mlx.normals.point_sets(proj,neighbors=32,smooth_iteration=10)
	mlx.remesh.surface_poisson_screened(proj)
	mlx.clean.close_holes(proj,hole_max_edge=1000,selected=False,sel_new_face=True,self_intersection=True)
	mlx.layers.delete(proj)
	proj.run_script()
if __name__ == "__main__":
        #pc2stl("result.asc")
        pass
