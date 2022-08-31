//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: StaticeEntityInstance.cs
//------------------------------------------------------------

using System;
using System.Numerics;
using System.Runtime.InteropServices;

namespace KMLEngine.Managed.Common.World.StaticEntity {
    [StructLayout(LayoutKind.Sequential)]
    public struct StaticEntityInstance {
        private uint m_data;
        public Vector3 Position;
        public Quaternion Rotation;

        public StaticEntityInstance(Vector3 position, Quaternion rotation, StaticEntityType type = StaticEntityType.None, uint metaData = 0) {
            m_data = 0;
            Position = position;
            Rotation = rotation;

            Type = type;
            MetaData = metaData;
        }
        
        public StaticEntityType Type {
            get => (StaticEntityType)(m_data & 0xFFFFE000u >> 13);
            set {
                m_data &= 0x1FFFu;
                m_data |= (uint)value << 13;
            }
        }

        public uint MetaData {
            get => m_data & 0x1FFFu;
            set {
                m_data &= 0xFFFFE000u;
                m_data |= value;
            }
        }

        public static bool operator ==(StaticEntityInstance a, StaticEntityInstance b) {
            return a.Position == b.Position && a.Rotation == b.Rotation && a.m_data == b.m_data;
        }

        public static bool operator !=(StaticEntityInstance a, StaticEntityInstance b) {
            return a.Position != b.Position || a.Rotation != b.Rotation || a.m_data != b.m_data;
        }

        public bool Equals(StaticEntityInstance other) {
            return m_data == other.m_data && Position.Equals(other.Position) && Rotation.Equals(other.Rotation);
        }

        public override bool Equals(object obj) {
            return obj is StaticEntityInstance other && Equals(other);
        }

        public override int GetHashCode() {
            return HashCode.Combine(m_data, Position, Rotation);
        }
    }
}