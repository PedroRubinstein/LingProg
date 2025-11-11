import os
import sys
import matplotlib


def _select_backend():
    """Try to switch from Agg to an interactive backend when possible.
    Honors MPLBACKEND if set. Tries TkAgg, then Qt5Agg, then GTK3Agg when a display is present.
    """
    # Respect explicit user choice
    if os.environ.get("MPLBACKEND"):
        return

    current = str(matplotlib.get_backend()).lower()
    has_display = bool(os.environ.get("DISPLAY")) or bool(os.environ.get("WAYLAND_DISPLAY"))

    if "agg" in current and has_display:
        for candidate in ("TkAgg", "Qt5Agg", "GTK3Agg"):
            try:
                matplotlib.use(candidate, force=True)
                break
            except Exception:
                print(f"[plotter.py] Could not switch backend ({candidate}); trying next", file=sys.stderr)
                continue


import matplotlib.pyplot as plt
from matplotlib.patches import Circle

_select_backend()

def _finalize_show(fig):
    try:
        backend = str(plt.get_backend()).lower()
        has_display = bool(os.environ.get("DISPLAY"))
        print(f"[plotter.py] Backend: {backend}, DISPLAY: {has_display}", file=sys.stderr)
        # Avoid calling plt.show() on non-interactive backends like Agg
        if ("agg" in backend) or (not has_display):
            raise RuntimeError(f"Non-interactive backend: {backend} or no DISPLAY")
        plt.show()
    except Exception as e:
        out = os.path.abspath("plot.png")
        fig.savefig(out, dpi=150, bbox_inches="tight")
        print(f"[plotter.py] Could not show figure ({e}); saved to {out}", file=sys.stderr)

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
            # Unknown: skip or log
            pass

    ax.set_xlabel('X-axis')
    ax.set_ylabel('Y-axis')
    ax.set_title('Geometric Objects')
    ax.grid(True)
    ax.set_aspect('equal', adjustable='box')
    _finalize_show(fig)