import os
import sys
import matplotlib

# FIX: Robust Backend Selection
try:
    matplotlib.use("Qt5Agg")
except ImportError:
    # If Qt5Agg is missing, let matplotlib pick the default
    print("[plotter.py] Warning: Qt5Agg backend not found. Using default.", file=sys.stderr)
    pass

import matplotlib.pyplot as plt
from matplotlib.patches import Circle

# Global variable to store the last figure
_last_figure = None

def plot_objects(shapes):
    """
    Plot a heterogeneous collection of shapes.
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
                ax.plot([cx], [cy], 'x', color='tab:green')
            except Exception as e:
                print(f"[plotter.py] ERROR in circumference processing: {e}", file=sys.stderr)
        elif t == 'line':
            x = list(s.get('x', []))
            y = list(s.get('y', []))
            if len(x) == 2 and len(y) == 2:
                ax.plot(x, y, '-k', linewidth=1.5)
        elif t == 'vector':
            try:
                x = s.get('x', 0)
                y = s.get('y', 0)
                ax.arrow(0, 0, x, y, head_width=0.15, head_length=0.1, fc='tab:red', ec='tab:red')
                ax.plot([x], [y], 'ro', markersize=4)
            except Exception as e:
                print(f"[plotter.py] ERROR in vector processing: {e}", file=sys.stderr)
        else:
            pass

    ax.set_xlabel('X-axis')
    ax.set_ylabel('Y-axis')
    ax.grid(True)
    ax.set_aspect('equal', adjustable='box')
    
    global _last_figure
    _last_figure = fig
    
    try:
        backend = str(plt.get_backend()).lower()
        has_display = bool(os.environ.get("DISPLAY"))
        if ("qtagg" in backend) or (not has_display):
            # raise RuntimeError(f"Non-interactive backend: {backend}")
            # Just print warning instead of crashing
            pass
            
        plt.show()
        # NOTE: Keeping the figure object alive even after close is tricky in some backends.
        # But we rely on _last_figure pointing to the Figure instance.
    except Exception as e:
        out = os.path.abspath("plot.png")
        fig.savefig(out, dpi=150, bbox_inches="tight")
        print(f"[plotter.py] Could not show figure ({e}); saved to {out}", file=sys.stderr)

def save_figure(filename):
    """
    Save the last generated figure to the specified filename.
    """
    global _last_figure
    if _last_figure is None:
        print("[plotter.py] Error: No figure to save. Generate a plot first.", file=sys.stderr)
        return False
    
    try:
        _last_figure.savefig(filename, dpi=150, bbox_inches="tight")
        print(f"[plotter.py] Figure saved to {filename}", file=sys.stderr)
        return True
    except Exception as e:
        print(f"[plotter.py] Error saving figure to {filename}: {e}", file=sys.stderr)
        return False
