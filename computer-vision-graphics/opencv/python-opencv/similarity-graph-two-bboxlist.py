import networkx as nx
import json
import os

def bbox_graph(bbox_list):
    G = nx.Graph()
    for bbox in bbox_list:
        G.add_node(bbox)
        for other in bbox_list:
            if is_spatially_adjacent(bbox, other):
                G.add_edge(bbox, other)
    return G

def is_spatially_adjacent(bbox1, bbox2):
    # Check if two bounding boxes are spatially adjacent
    # based on geometry, overlap, etc.
    # Return True or False
    x1, y1, w1, h1 = bbox1[0], bbox2[1], bbox1[2]-bbox1[0], bbox1[3]-bbox1[1]  
    x2, y2, w2, h2 = bbox2[0], bbox2[1],  bbox2[2]-bbox2[0], bbox2[3]-bbox2[1]
    
    # Check horizontal adjacency
    if abs(x1 - x2) < min(w1, w2):
        return True
    
    # Check vertical adjacency 
    if abs(y1 - y2) < min(h1, h2):
        return True

    # Check diagonal adjacency
    if abs(x1 - x2) < sqrt(w1*w1 + h1*h1) and abs(y1 - y2) < sqrt(w2*w2 + h2*h2):
        return True

    return False 

def layout_similarity(bbox_list1, bbox_list2):
    G1 = bbox_graph(bbox_list1) 
    G2 = bbox_graph(bbox_list2)
    
    # Calculate graph edit distance 
    # Lower distance indicates more similar layout
    distance = nx.graph_edit_distance(G1, G2) 
    
    return 1 / (distance + 1) # Convert to similarity score

dir = "/Users/royzheng/Documents/PHIData1-1080p-templates"
file1 = open(os.path.join(dir, "Image022.json")) 
jobj1 = json.load(file1) 
file2 = open(os.path.join(dir, "Image027.json")) 
jobj2 = json.load(file2) 

bbox_list1 = [bbox["bbox"] for bbox in jobj1] # list of bounding boxes for page 1 
bbox_list2 = [bbox["bbox"] for bbox in jobj2] # list of bounding boxes for page 2

sim = layout_similarity(bbox_list1, bbox_list2)
print("Layout Similarity:", sim)
