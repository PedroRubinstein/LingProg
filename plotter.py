import os
import sys
import matplotlib
matplotlib.use("Qt5Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import Circle

# Global variable to store the last figure
_last_figure = None

def plot_objects(shapes):
    """
    Plot a heterogeneous collection of shapes.
    Each shape is a dict with a 'type' field among {'point','polygon','circumference'} and
    the required parameters:
      - point: {'type':'point','x':float,'y':float}
      - polygon: {'type':'polygon','x':list[float],'y':list[float]}
      - circumference: {'type':'circumference','center':(x,y),'radius':float}
    """
    fig, ax = plt.subplots()
    for s in shapes:
        t = s.get('type', 'unknown')
        if t == 'point':
            ax.plot([s['x']], [s['y']], 'o', color='tab:blue')
        elif t == 'polygon':
            x = list(s.get('x', []))
            y = list(s.get('y', []))
            if x and y and (x[0] != x[-1] or y[0] != y[-1]):
                x.append(x[0])
                y.append(y[0])
            ax.plot(x, y, '-o', color='tab:orange')
        elif t == 'circumference':
            try:
                center = s['center']
                r = s['radius']
                cx, cy = center
                circ = Circle((cx, cy), r, fill=False, color='tab:green')
                ax.add_patch(circ)
                # Also plot center
                ax.plot([cx], [cy], 'x', color='tab:green')
            except Exception as e:
                print(f"[plotter.py] ERROR in circumference processing: {e}", file=sys.stderr)
        elif t == 'line':
            x = list(s.get('x', []))
            y = list(s.get('y', []))
            if len(x) == 2 and len(y) == 2:
                ax.plot(x, y, '-k', linewidth=1.5)
        else:
            #unknown: skip
            pass

    ax.set_xlabel('X-axis')
    ax.set_ylabel('Y-axis')
    ax.grid(True)
    ax.set_aspect('equal', adjustable='box')
    
    # Store the figure globally for later saving
    global _last_figure
    _last_figure = fig
    
    try:
        backend = str(plt.get_backend()).lower()
        has_display = bool(os.environ.get("DISPLAY"))
        # Avoid calling plt.show() on non-interactive backends like qtAgg
        if ("qtagg" in backend) or (not has_display):
            print("here", backend, has_display)
            raise RuntimeError(f"Non-interactive backend: {backend} or no DISPLAY: has? {has_display}")
        plt.show()
        plt.close()
    except Exception as e:
        out = os.path.abspath("plot.png")
        fig.savefig(out, dpi=150, bbox_inches="tight")
        print(f"[plotter.py] Could not show figure ({e}); saved to {out}", file=sys.stderr)

def save_figure(filename):
    """
    Save the last generated figure to the specified filename.
    Returns True if successful, False otherwise.
    """
    global _last_figure
    if _last_figure is None:
        print("[plotter.py] Error: No figure to save", file=sys.stderr)
        return False
    
    try:
        _last_figure.savefig(filename, dpi=150, bbox_inches="tight")
        print(f"[plotter.py] Figure saved to {filename}", file=sys.stderr)
        return True
    except Exception as e:
        print(f"[plotter.py] Error saving figure to {filename}: {e}", file=sys.stderr)
        return False