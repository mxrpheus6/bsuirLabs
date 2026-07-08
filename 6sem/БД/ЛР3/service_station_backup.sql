--
-- PostgreSQL database dump
--

-- Dumped from database version 17.2
-- Dumped by pg_dump version 17.2

-- Started on 2025-02-27 14:18:51

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET transaction_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 4 (class 2615 OID 2200)
-- Name: public; Type: SCHEMA; Schema: -; Owner: pg_database_owner
--

CREATE SCHEMA public;


ALTER SCHEMA public OWNER TO pg_database_owner;

--
-- TOC entry 5079 (class 0 OID 0)
-- Dependencies: 4
-- Name: SCHEMA public; Type: COMMENT; Schema: -; Owner: pg_database_owner
--

COMMENT ON SCHEMA public IS 'standard public schema';


SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 223 (class 1259 OID 45261)
-- Name: car; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.car (
    id integer NOT NULL,
    plate_number character varying(20) NOT NULL,
    manufacturer character varying(50) NOT NULL,
    model character varying(50) NOT NULL,
    engine_type character varying(20) NOT NULL,
    manufacture_year date NOT NULL,
    client_id integer NOT NULL
);


ALTER TABLE public.car OWNER TO postgres;

--
-- TOC entry 222 (class 1259 OID 45260)
-- Name: car_client_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.car_client_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.car_client_id_seq OWNER TO postgres;

--
-- TOC entry 5080 (class 0 OID 0)
-- Dependencies: 222
-- Name: car_client_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.car_client_id_seq OWNED BY public.car.client_id;


--
-- TOC entry 221 (class 1259 OID 45259)
-- Name: car_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.car_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.car_id_seq OWNER TO postgres;

--
-- TOC entry 5081 (class 0 OID 0)
-- Dependencies: 221
-- Name: car_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.car_id_seq OWNED BY public.car.id;


--
-- TOC entry 220 (class 1259 OID 45251)
-- Name: client; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.client (
    id integer NOT NULL,
    first_name character varying(25) NOT NULL,
    last_name character varying(25) NOT NULL,
    middle_name character varying(25),
    phone_number character varying(20) NOT NULL,
    email character varying(255),
    address character varying(255),
    registration_date date NOT NULL
);


ALTER TABLE public.client OWNER TO postgres;

--
-- TOC entry 219 (class 1259 OID 45250)
-- Name: client_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.client_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.client_id_seq OWNER TO postgres;

--
-- TOC entry 5082 (class 0 OID 0)
-- Dependencies: 219
-- Name: client_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.client_id_seq OWNED BY public.client.id;


--
-- TOC entry 254 (class 1259 OID 45353)
-- Name: completed_service; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.completed_service (
    id integer NOT NULL,
    completed_at date,
    status character varying(50) NOT NULL,
    work_order_id integer NOT NULL,
    work_area_id integer NOT NULL,
    service_id integer NOT NULL
);


ALTER TABLE public.completed_service OWNER TO postgres;

--
-- TOC entry 257 (class 1259 OID 45494)
-- Name: completed_service_employee; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.completed_service_employee (
    completed_service_id integer NOT NULL,
    employee_id integer NOT NULL
);


ALTER TABLE public.completed_service_employee OWNER TO postgres;

--
-- TOC entry 255 (class 1259 OID 45492)
-- Name: completed_service_employee_completed_service_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.completed_service_employee_completed_service_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.completed_service_employee_completed_service_id_seq OWNER TO postgres;

--
-- TOC entry 5083 (class 0 OID 0)
-- Dependencies: 255
-- Name: completed_service_employee_completed_service_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.completed_service_employee_completed_service_id_seq OWNED BY public.completed_service_employee.completed_service_id;


--
-- TOC entry 256 (class 1259 OID 45493)
-- Name: completed_service_employee_employee_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.completed_service_employee_employee_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.completed_service_employee_employee_id_seq OWNER TO postgres;

--
-- TOC entry 5084 (class 0 OID 0)
-- Dependencies: 256
-- Name: completed_service_employee_employee_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.completed_service_employee_employee_id_seq OWNED BY public.completed_service_employee.employee_id;


--
-- TOC entry 250 (class 1259 OID 45348)
-- Name: completed_service_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.completed_service_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.completed_service_id_seq OWNER TO postgres;

--
-- TOC entry 5085 (class 0 OID 0)
-- Dependencies: 250
-- Name: completed_service_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.completed_service_id_seq OWNED BY public.completed_service.id;


--
-- TOC entry 253 (class 1259 OID 45352)
-- Name: completed_service_service_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.completed_service_service_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.completed_service_service_id_seq OWNER TO postgres;

--
-- TOC entry 5086 (class 0 OID 0)
-- Dependencies: 253
-- Name: completed_service_service_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.completed_service_service_id_seq OWNED BY public.completed_service.service_id;


--
-- TOC entry 252 (class 1259 OID 45350)
-- Name: completed_service_work_area_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.completed_service_work_area_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.completed_service_work_area_id_seq OWNER TO postgres;

--
-- TOC entry 5087 (class 0 OID 0)
-- Dependencies: 252
-- Name: completed_service_work_area_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.completed_service_work_area_id_seq OWNED BY public.completed_service.work_area_id;


--
-- TOC entry 251 (class 1259 OID 45349)
-- Name: completed_service_work_order_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.completed_service_work_order_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.completed_service_work_order_id_seq OWNER TO postgres;

--
-- TOC entry 5088 (class 0 OID 0)
-- Dependencies: 251
-- Name: completed_service_work_order_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.completed_service_work_order_id_seq OWNED BY public.completed_service.work_order_id;


--
-- TOC entry 240 (class 1259 OID 45317)
-- Name: consumable_material; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.consumable_material (
    id integer NOT NULL,
    name character varying(50) NOT NULL,
    unit character varying(20) NOT NULL,
    unit_cost numeric(10,2) NOT NULL,
    current_stock numeric(10,2) NOT NULL
);


ALTER TABLE public.consumable_material OWNER TO postgres;

--
-- TOC entry 239 (class 1259 OID 45316)
-- Name: consumable_material_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.consumable_material_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.consumable_material_id_seq OWNER TO postgres;

--
-- TOC entry 5089 (class 0 OID 0)
-- Dependencies: 239
-- Name: consumable_material_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.consumable_material_id_seq OWNED BY public.consumable_material.id;


--
-- TOC entry 229 (class 1259 OID 45279)
-- Name: employee; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.employee (
    id integer NOT NULL,
    first_name character varying(25) NOT NULL,
    last_name character varying(25) NOT NULL,
    middle_name character varying(25) NOT NULL,
    gender "char" NOT NULL,
    date_of_birth date NOT NULL,
    address character varying(255) NOT NULL,
    phone_number character varying(20) NOT NULL,
    medical_certificate_expiry date NOT NULL,
    salary numeric(10,2) NOT NULL,
    position_id integer NOT NULL
);


ALTER TABLE public.employee OWNER TO postgres;

--
-- TOC entry 227 (class 1259 OID 45277)
-- Name: employee_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.employee_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.employee_id_seq OWNER TO postgres;

--
-- TOC entry 5090 (class 0 OID 0)
-- Dependencies: 227
-- Name: employee_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.employee_id_seq OWNED BY public.employee.id;


--
-- TOC entry 228 (class 1259 OID 45278)
-- Name: employee_position_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.employee_position_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.employee_position_id_seq OWNER TO postgres;

--
-- TOC entry 5091 (class 0 OID 0)
-- Dependencies: 228
-- Name: employee_position_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.employee_position_id_seq OWNED BY public.employee.position_id;


--
-- TOC entry 231 (class 1259 OID 45287)
-- Name: position; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."position" (
    id integer NOT NULL,
    name character varying(50)
);


ALTER TABLE public."position" OWNER TO postgres;

--
-- TOC entry 230 (class 1259 OID 45286)
-- Name: position_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.position_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.position_id_seq OWNER TO postgres;

--
-- TOC entry 5092 (class 0 OID 0)
-- Dependencies: 230
-- Name: position_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.position_id_seq OWNED BY public."position".id;


--
-- TOC entry 238 (class 1259 OID 45310)
-- Name: service; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.service (
    id integer NOT NULL,
    name character varying(50) NOT NULL,
    description character varying(255),
    price numeric(10,2) NOT NULL,
    warranty_period character varying(50)
);


ALTER TABLE public.service OWNER TO postgres;

--
-- TOC entry 243 (class 1259 OID 45325)
-- Name: service_consumable_material; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.service_consumable_material (
    service_id integer NOT NULL,
    consumable_material_id integer NOT NULL,
    amount numeric(10,2) NOT NULL
);


ALTER TABLE public.service_consumable_material OWNER TO postgres;

--
-- TOC entry 242 (class 1259 OID 45324)
-- Name: service_consumable_material_consumable_material_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.service_consumable_material_consumable_material_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.service_consumable_material_consumable_material_id_seq OWNER TO postgres;

--
-- TOC entry 5093 (class 0 OID 0)
-- Dependencies: 242
-- Name: service_consumable_material_consumable_material_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.service_consumable_material_consumable_material_id_seq OWNED BY public.service_consumable_material.consumable_material_id;


--
-- TOC entry 241 (class 1259 OID 45323)
-- Name: service_consumable_material_service_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.service_consumable_material_service_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.service_consumable_material_service_id_seq OWNER TO postgres;

--
-- TOC entry 5094 (class 0 OID 0)
-- Dependencies: 241
-- Name: service_consumable_material_service_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.service_consumable_material_service_id_seq OWNED BY public.service_consumable_material.service_id;


--
-- TOC entry 249 (class 1259 OID 45343)
-- Name: service_employee; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.service_employee (
    service_id integer NOT NULL,
    employee_id integer NOT NULL
);


ALTER TABLE public.service_employee OWNER TO postgres;

--
-- TOC entry 248 (class 1259 OID 45342)
-- Name: service_employee_employee_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.service_employee_employee_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.service_employee_employee_id_seq OWNER TO postgres;

--
-- TOC entry 5095 (class 0 OID 0)
-- Dependencies: 248
-- Name: service_employee_employee_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.service_employee_employee_id_seq OWNED BY public.service_employee.employee_id;


--
-- TOC entry 247 (class 1259 OID 45341)
-- Name: service_employee_service_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.service_employee_service_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.service_employee_service_id_seq OWNER TO postgres;

--
-- TOC entry 5096 (class 0 OID 0)
-- Dependencies: 247
-- Name: service_employee_service_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.service_employee_service_id_seq OWNED BY public.service_employee.service_id;


--
-- TOC entry 237 (class 1259 OID 45309)
-- Name: service_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.service_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.service_id_seq OWNER TO postgres;

--
-- TOC entry 5097 (class 0 OID 0)
-- Dependencies: 237
-- Name: service_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.service_id_seq OWNED BY public.service.id;


--
-- TOC entry 234 (class 1259 OID 45295)
-- Name: work_area; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.work_area (
    id integer NOT NULL,
    name character varying(50) NOT NULL,
    status character varying(50) NOT NULL,
    last_service_date date,
    work_area_type_id integer NOT NULL
);


ALTER TABLE public.work_area OWNER TO postgres;

--
-- TOC entry 232 (class 1259 OID 45293)
-- Name: work_area_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.work_area_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.work_area_id_seq OWNER TO postgres;

--
-- TOC entry 5098 (class 0 OID 0)
-- Dependencies: 232
-- Name: work_area_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.work_area_id_seq OWNED BY public.work_area.id;


--
-- TOC entry 246 (class 1259 OID 45334)
-- Name: work_area_service; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.work_area_service (
    work_area_id integer NOT NULL,
    service_id integer NOT NULL
);


ALTER TABLE public.work_area_service OWNER TO postgres;

--
-- TOC entry 245 (class 1259 OID 45333)
-- Name: work_area_service_service_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.work_area_service_service_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.work_area_service_service_id_seq OWNER TO postgres;

--
-- TOC entry 5099 (class 0 OID 0)
-- Dependencies: 245
-- Name: work_area_service_service_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.work_area_service_service_id_seq OWNED BY public.work_area_service.service_id;


--
-- TOC entry 244 (class 1259 OID 45332)
-- Name: work_area_service_work_area_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.work_area_service_work_area_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.work_area_service_work_area_id_seq OWNER TO postgres;

--
-- TOC entry 5100 (class 0 OID 0)
-- Dependencies: 244
-- Name: work_area_service_work_area_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.work_area_service_work_area_id_seq OWNED BY public.work_area_service.work_area_id;


--
-- TOC entry 236 (class 1259 OID 45303)
-- Name: work_area_type; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.work_area_type (
    id integer NOT NULL,
    name character varying(50) NOT NULL
);


ALTER TABLE public.work_area_type OWNER TO postgres;

--
-- TOC entry 235 (class 1259 OID 45302)
-- Name: work_area_type_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.work_area_type_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.work_area_type_id_seq OWNER TO postgres;

--
-- TOC entry 5101 (class 0 OID 0)
-- Dependencies: 235
-- Name: work_area_type_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.work_area_type_id_seq OWNED BY public.work_area_type.id;


--
-- TOC entry 233 (class 1259 OID 45294)
-- Name: work_area_work_zone_type_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.work_area_work_zone_type_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.work_area_work_zone_type_id_seq OWNER TO postgres;

--
-- TOC entry 5102 (class 0 OID 0)
-- Dependencies: 233
-- Name: work_area_work_zone_type_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.work_area_work_zone_type_id_seq OWNED BY public.work_area.work_area_type_id;


--
-- TOC entry 226 (class 1259 OID 45270)
-- Name: work_order; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.work_order (
    id integer NOT NULL,
    public_id character varying(20) NOT NULL,
    created_at date NOT NULL,
    competed_at date,
    comment character varying(255),
    total_cost numeric(10,2),
    car_id integer NOT NULL
);


ALTER TABLE public.work_order OWNER TO postgres;

--
-- TOC entry 225 (class 1259 OID 45269)
-- Name: work_order_car_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.work_order_car_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.work_order_car_id_seq OWNER TO postgres;

--
-- TOC entry 5103 (class 0 OID 0)
-- Dependencies: 225
-- Name: work_order_car_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.work_order_car_id_seq OWNED BY public.work_order.car_id;


--
-- TOC entry 224 (class 1259 OID 45268)
-- Name: work_order_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.work_order_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.work_order_id_seq OWNER TO postgres;

--
-- TOC entry 5104 (class 0 OID 0)
-- Dependencies: 224
-- Name: work_order_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.work_order_id_seq OWNED BY public.work_order.id;


--
-- TOC entry 4825 (class 2604 OID 45264)
-- Name: car id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.car ALTER COLUMN id SET DEFAULT nextval('public.car_id_seq'::regclass);


--
-- TOC entry 4826 (class 2604 OID 45265)
-- Name: car client_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.car ALTER COLUMN client_id SET DEFAULT nextval('public.car_client_id_seq'::regclass);


--
-- TOC entry 4824 (class 2604 OID 45254)
-- Name: client id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.client ALTER COLUMN id SET DEFAULT nextval('public.client_id_seq'::regclass);


--
-- TOC entry 4843 (class 2604 OID 45356)
-- Name: completed_service id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.completed_service ALTER COLUMN id SET DEFAULT nextval('public.completed_service_id_seq'::regclass);


--
-- TOC entry 4844 (class 2604 OID 45357)
-- Name: completed_service work_order_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.completed_service ALTER COLUMN work_order_id SET DEFAULT nextval('public.completed_service_work_order_id_seq'::regclass);


--
-- TOC entry 4845 (class 2604 OID 45358)
-- Name: completed_service work_area_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.completed_service ALTER COLUMN work_area_id SET DEFAULT nextval('public.completed_service_work_area_id_seq'::regclass);


--
-- TOC entry 4846 (class 2604 OID 45360)
-- Name: completed_service service_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.completed_service ALTER COLUMN service_id SET DEFAULT nextval('public.completed_service_service_id_seq'::regclass);


--
-- TOC entry 4847 (class 2604 OID 45497)
-- Name: completed_service_employee completed_service_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.completed_service_employee ALTER COLUMN completed_service_id SET DEFAULT nextval('public.completed_service_employee_completed_service_id_seq'::regclass);


--
-- TOC entry 4848 (class 2604 OID 45498)
-- Name: completed_service_employee employee_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.completed_service_employee ALTER COLUMN employee_id SET DEFAULT nextval('public.completed_service_employee_employee_id_seq'::regclass);


--
-- TOC entry 4836 (class 2604 OID 45320)
-- Name: consumable_material id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.consumable_material ALTER COLUMN id SET DEFAULT nextval('public.consumable_material_id_seq'::regclass);


--
-- TOC entry 4829 (class 2604 OID 45282)
-- Name: employee id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.employee ALTER COLUMN id SET DEFAULT nextval('public.employee_id_seq'::regclass);


--
-- TOC entry 4830 (class 2604 OID 45283)
-- Name: employee position_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.employee ALTER COLUMN position_id SET DEFAULT nextval('public.employee_position_id_seq'::regclass);


--
-- TOC entry 4831 (class 2604 OID 45290)
-- Name: position id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."position" ALTER COLUMN id SET DEFAULT nextval('public.position_id_seq'::regclass);


--
-- TOC entry 4835 (class 2604 OID 45313)
-- Name: service id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.service ALTER COLUMN id SET DEFAULT nextval('public.service_id_seq'::regclass);


--
-- TOC entry 4837 (class 2604 OID 45328)
-- Name: service_consumable_material service_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.service_consumable_material ALTER COLUMN service_id SET DEFAULT nextval('public.service_consumable_material_service_id_seq'::regclass);


--
-- TOC entry 4838 (class 2604 OID 45329)
-- Name: service_consumable_material consumable_material_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.service_consumable_material ALTER COLUMN consumable_material_id SET DEFAULT nextval('public.service_consumable_material_consumable_material_id_seq'::regclass);


--
-- TOC entry 4841 (class 2604 OID 45346)
-- Name: service_employee service_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.service_employee ALTER COLUMN service_id SET DEFAULT nextval('public.service_employee_service_id_seq'::regclass);


--
-- TOC entry 4842 (class 2604 OID 45347)
-- Name: service_employee employee_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.service_employee ALTER COLUMN employee_id SET DEFAULT nextval('public.service_employee_employee_id_seq'::regclass);


--
-- TOC entry 4832 (class 2604 OID 45298)
-- Name: work_area id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.work_area ALTER COLUMN id SET DEFAULT nextval('public.work_area_id_seq'::regclass);


--
-- TOC entry 4833 (class 2604 OID 45299)
-- Name: work_area work_area_type_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.work_area ALTER COLUMN work_area_type_id SET DEFAULT nextval('public.work_area_work_zone_type_id_seq'::regclass);


--
-- TOC entry 4839 (class 2604 OID 45337)
-- Name: work_area_service work_area_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.work_area_service ALTER COLUMN work_area_id SET DEFAULT nextval('public.work_area_service_work_area_id_seq'::regclass);


--
-- TOC entry 4840 (class 2604 OID 45338)
-- Name: work_area_service service_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.work_area_service ALTER COLUMN service_id SET DEFAULT nextval('public.work_area_service_service_id_seq'::regclass);


--
-- TOC entry 4834 (class 2604 OID 45306)
-- Name: work_area_type id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.work_area_type ALTER COLUMN id SET DEFAULT nextval('public.work_area_type_id_seq'::regclass);


--
-- TOC entry 4827 (class 2604 OID 45273)
-- Name: work_order id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.work_order ALTER COLUMN id SET DEFAULT nextval('public.work_order_id_seq'::regclass);


--
-- TOC entry 4828 (class 2604 OID 45274)
-- Name: work_order car_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.work_order ALTER COLUMN car_id SET DEFAULT nextval('public.work_order_car_id_seq'::regclass);


--
-- TOC entry 5039 (class 0 OID 45261)
-- Dependencies: 223
-- Data for Name: car; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.car (id, plate_number, manufacturer, model, engine_type, manufacture_year, client_id) FROM stdin;
1	0001 PC-2	Ford	Focus	Дизель	2023-01-25	3
2	0002 KA-3	BMW	X5	Электро	2011-08-09	4
3	0003 AI-4	Mercedes-Benz	E-Class	Бензин	2007-08-25	5
4	0004 ET-5	Audi	A6	Дизель	2019-01-05	6
5	0005 KH-6	Honda	Civic	Электро	2009-04-15	7
6	0006 TM-7	Toyota	Camry	Бензин	2001-09-02	8
7	0007 MM-1	Ford	Focus	Дизель	2003-12-31	9
8	0008 IE-2	BMW	X5	Электро	2019-11-09	10
9	0009 PP-3	Mercedes-Benz	E-Class	Бензин	2013-03-29	11
10	0010 EH-4	Audi	A6	Дизель	2002-05-20	12
11	0011 II-5	Honda	Civic	Электро	2013-01-11	13
12	0012 BI-6	Toyota	Camry	Бензин	2004-08-01	14
13	0013 BT-7	Ford	Focus	Дизель	2010-12-13	15
14	0014 PI-1	BMW	X5	Электро	2020-08-04	16
15	0015 TB-2	Mercedes-Benz	E-Class	Бензин	2015-08-30	17
16	0016 PP-3	Audi	A6	Дизель	2017-02-08	18
17	0017 CT-4	Honda	Civic	Электро	2022-08-06	19
18	0018 IM-5	Toyota	Camry	Бензин	2022-04-30	20
19	0019 CO-6	Ford	Focus	Дизель	2015-03-28	21
20	0020 AT-7	BMW	X5	Электро	2019-12-15	22
21	0021 TH-1	Mercedes-Benz	E-Class	Бензин	2006-01-22	23
22	0022 PB-2	Audi	A6	Дизель	2004-05-16	24
23	0023 HO-3	Honda	Civic	Электро	2003-03-23	25
24	0024 PH-4	Toyota	Camry	Бензин	2014-10-28	26
25	0025 AE-5	Ford	Focus	Дизель	2018-05-15	27
26	0026 MC-6	BMW	X5	Электро	2008-08-18	2
\.


--
-- TOC entry 5036 (class 0 OID 45251)
-- Dependencies: 220
-- Data for Name: client; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.client (id, first_name, last_name, middle_name, phone_number, email, address, registration_date) FROM stdin;
2	Павел	Казаченко	Евгеньевич	+375297777777	pkazachenkoo@gmail.com	Минск, Немига 3	2025-02-26
3	Максим	Солодков	Дмитриевич	+375297430475	mapsonclash@gmail.com	Минск, проспект Победителей, 53к1	2025-02-26
4	Руслан	Алхава	Абдулькаримович	+375291234567	ruslan.alkhava@gmail.com	Минск, ул. Ленина, 10	2023-01-01
5	Александр	Антоненко	Владимирович	+375292345678	sasha.antonenko@yandex.by	Минск, пр. Независимости, 25	2023-01-02
6	Матвей	Борисевич	Игоревич	+375293456789	matvey.borisevich@mail.ru	Минск, ул. Козлова, 15	2023-01-03
7	Дмитрий	Василевич	Викторович	+375294567890	dima.vasilevich@yahoo.com	Минск, ул. Сурганова, 30	2023-01-04
8	Вадим	Вильчинский	Сергеевич	+375295678901	vadim.vilchinsky@icloud.com	Минск, ул. Притыцкого, 45	2023-01-05
9	Артем	Гутковский	Сергеевич	+375296789012	artem.gutkovsky@outlook.com	Минск, ул. Толбухина, 50	2023-01-06
10	Павел	Дмитриев	Андреевич	+375297890123	pavel.dmitriev@rambler.ru	Минск, ул. Богдановича, 55	2023-01-07
11	Илья	Закоркин	Денисович	+375298901234	ilya.zakorkin@gmail.com	Минск, ул. Немига, 60	2023-01-08
12	Владислав	Ильюшевич	Сергеевич	+375299012345	vlad.ilyushevich@yandex.by	Минск, ул. Филимонова, 65	2023-01-09
13	Дмитрий	Кабачевский	Вячеславович	+375291123456	dima.kabachevsky@mail.ru	Минск, ул. Кальварийская, 70	2023-01-10
14	Олег	Борисов	Сергеевич	+375292234567	example@yahoo.com	Минск, ул. Романовская Слобода, 75	2023-01-11
15	Полина	Кароткая	Сергеевна	+375293345678	polina.korotkaya@icloud.com	Минск, ул. Ольшевского, 80	2023-01-12
16	Илья	Лагодич	Романович	+375294456789	ilya.lagodich@outlook.com	Минск, ул. Кульман, 85	2023-01-13
17	Даниил	Лешок	Андреевич	+375295567890	daniel.leshok@rambler.ru	Минск, ул. Скрыганова, 90	2023-01-14
18	Артём	Мальченко	Евгеньевич	+375296678901	artem.malchenko@gmail.com	Минск, ул. Лобанка, 95	2023-01-15
19	Иван	Манько	Кириллович	+375297789012	ivan.manko@yandex.by	Гомель, ул. Советская, 100	2023-01-16
20	Владислав	Моисеев	Сергеевич	+375298890123	vlad.moiseev@mail.ru	Минск, ул. Голубева, 105	2023-01-17
21	Артем	Наркевич	Сергеевич	+375299901234	artem.narkevich@yahoo.com	Минск, ул. Щорса, 110	2023-01-18
22	Константин	Пигулевский	Сергеевич	+375291012345	kostya.pigulevsky@icloud.com	Минск, ул. Плеханова, 115	2023-01-19
23	Леонид	Русецкий	Максимович	+375291123456	leonid.rusetsky@outlook.com	Минск, ул. Кропоткина, 120	2023-01-20
24	Артём	Слинько	Геннадьевич	+375292234567	artem.slinko@rambler.ru	Минск, ул. Лукьяновича, 125	2023-01-21
26	Юрий	Спасёнов	Леонидович	+375294456789	yury.spasenov@yandex.by	Гомель, ул. Ильича, 135	2023-01-23
27	Максим	Таврель	Дмитриевич	+375295567890	maxim.tavrel@mail.ru	Минск, ул. Лынькова, 140	2023-01-24
25	Илья	Кольянов	Дмитриевич	+375293345678	ilya.kolyanov@gmail.com	Минск, ул. Левкова, 130	2023-01-22
\.


--
-- TOC entry 5070 (class 0 OID 45353)
-- Dependencies: 254
-- Data for Name: completed_service; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.completed_service (id, completed_at, status, work_order_id, work_area_id, service_id) FROM stdin;
37	2025-02-01	Выполнено	1	1	1
38	2025-02-02	Выполнено	2	2	2
39	2025-02-03	Выполнено	3	3	3
40	2025-02-04	Выполнено	4	4	4
41	2025-02-05	Выполнено	5	5	5
42	2025-02-06	Выполнено	6	6	6
43	2025-02-07	Выполнено	7	1	7
44	2025-02-08	Выполнено	8	2	8
45	2025-02-09	Выполнено	9	3	9
46	2025-02-10	Выполнено	10	4	10
47	2025-02-11	Выполнено	11	5	11
48	2025-02-12	Выполнено	12	6	12
49	2025-02-13	Выполнено	13	1	13
50	2025-02-14	Выполнено	14	2	14
51	2025-02-15	Выполнено	15	3	15
52	2025-02-16	Выполнено	16	4	16
53	2025-02-17	Выполнено	17	5	17
54	2025-02-18	Выполнено	18	6	18
55	2025-02-19	Выполнено	19	1	19
56	2025-02-20	Выполнено	20	2	20
57	2025-02-21	Выполнено	21	3	21
58	2025-02-22	Выполнено	22	4	22
59	2025-02-23	Выполнено	23	5	23
60	2025-02-24	Выполнено	24	6	24
61	2025-02-25	Выполнено	25	1	25
62	2025-02-26	Выполнено	26	2	26
\.


--
-- TOC entry 5073 (class 0 OID 45494)
-- Dependencies: 257
-- Data for Name: completed_service_employee; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.completed_service_employee (completed_service_id, employee_id) FROM stdin;
37	3
38	5
39	7
40	8
41	6
42	6
43	7
44	4
45	10
46	9
47	12
48	12
49	13
50	14
51	15
52	16
53	17
54	7
55	5
56	14
57	8
58	16
59	13
60	11
61	14
62	9
\.


--
-- TOC entry 5056 (class 0 OID 45317)
-- Dependencies: 240
-- Data for Name: consumable_material; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.consumable_material (id, name, unit, unit_cost, current_stock) FROM stdin;
1	Моторное масло 5W-30	литр	25.00	200.00
2	Тормозная жидкость DOT-4	литр	15.00	100.00
3	Охлаждающая жидкость G12	литр	12.00	150.00
4	Фильтр масляный	шт	18.00	50.00
5	Фильтр воздушный	шт	20.00	40.00
6	Фильтр топливный	шт	22.00	30.00
7	Фильтр салонный	шт	25.00	45.00
8	Свечи зажигания	комплект	60.00	25.00
9	Ремень ГРМ	шт	90.00	15.00
10	Ремень генератора	шт	50.00	20.00
11	Антифриз	литр	10.00	100.00
12	Масляный насос	шт	350.00	10.00
13	Тормозные колодки	комплект	80.00	30.00
14	Тормозные диски	комплект	200.00	15.00
15	Гидравлическое масло	литр	30.00	80.00
16	Жидкость ГУР	литр	25.00	60.00
17	Стеклоомывающая жидкость	литр	5.00	200.00
18	Клей-герметик	тюбик	10.00	50.00
19	Аккумулятор 75Ah	шт	250.00	12.00
20	Щетки стеклоочистителя	пара	35.00	40.00
21	Подшипник ступицы	шт	90.00	20.00
22	Амортизатор передний	шт	180.00	15.00
23	Амортизатор задний	шт	160.00	15.00
24	Шаровая опора	шт	70.00	25.00
25	Рулевой наконечник	шт	75.00	25.00
26	Комплект ГРМ	комплект	300.00	10.00
\.


--
-- TOC entry 5045 (class 0 OID 45279)
-- Dependencies: 229
-- Data for Name: employee; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.employee (id, first_name, last_name, middle_name, gender, date_of_birth, address, phone_number, medical_certificate_expiry, salary, position_id) FROM stdin;
1	Иван	Петров	Сергеевич	\\320	1985-03-15	Минск, ул. Ленина, 10	+375291234567	2025-03-15	1500.00	1
2	Алексей	Смирнов	Дмитриевич	\\320	1990-05-20	Минск, ул. Победителей, 5	+375291234568	2025-05-20	1600.00	1
3	Дмитрий	Козлов	Олегович	\\320	1991-07-09	Минск, ул. Ломоносова, 3	+375291234569	2025-07-09	1700.00	1
4	Сергей	Михайлов	Юрьевич	\\320	1983-10-22	Минск, ул. Пролетарская, 20	+375291234570	2025-10-22	1800.00	2
5	Андрей	Лебедев	Геннадиевич	\\320	1988-12-30	Минск, ул. Маяковского, 2	+375291234571	2025-12-30	1900.00	2
6	Татьяна	Иванова	Владимировна	\\320	1993-04-17	Минск, ул. Советская, 4	+375291234572	2025-04-17	1500.00	3
7	Евгений	Павлов	Анатольевич	\\320	1986-08-11	Минск, ул. Куйбышева, 7	+375291234573	2025-08-11	1700.00	3
8	Михаил	Фёдоров	Иванович	\\320	1991-03-25	Минск, ул. Дзержинского, 16	+375291234574	2025-03-25	1300.00	4
9	Александр	Борисов	Степанович	\\320	1989-02-13	Минск, ул. Калиновского, 5	+375291234575	2025-02-13	1400.00	4
10	Анна	Романовская	Станиславовна	\\320	1990-01-18	Минск, ул. Якуба Коласа, 9	+375291234576	2025-01-18	1800.00	5
11	Игорь	Филатов	Михайлович	\\320	1984-09-05	Минск, ул. Козлова, 8	+375291234577	2025-09-05	1700.00	5
12	Георгий	Петров	Игоревич	\\320	1982-05-15	Минск, ул. Лермонтова, 19	+375291234578	2025-05-15	2000.00	7
13	Анастасия	Егорова	Викторовна	\\320	1994-11-25	Минск, ул. Пушкина, 18	+375291234579	2025-11-25	1200.00	12
14	Роман	Дьяков	Петрович	\\320	1992-07-03	Минск, ул. Захарова, 21	+375291234580	2025-07-03	1500.00	8
15	Ольга	Семенова	Геннадиевна	\\320	1985-04-09	Минск, ул. Гагарина, 6	+375291234581	2025-04-09	1700.00	9
16	Константин	Медведев	Максимович	\\320	1984-08-29	Минск, ул. Лукина, 12	+375291234582	2025-08-29	2300.00	10
17	Маргарита	Кравцова	Ильинична	\\320	1992-12-10	Минск, ул. Пархоменко, 3	+375291234583	2025-12-10	1500.00	11
18	Денис	Костин	Андреевич	\\320	1980-01-30	Минск, ул. Шевченко, 5	+375291234584	2025-01-30	2200.00	13
19	Владимир	Беляев	Семенович	\\320	1989-07-14	Минск, ул. Колесникова, 25	+375291234585	2025-07-14	2500.00	14
20	Екатерина	Громова	Сергеевна	\\320	1991-06-17	Минск, ул. Черняховского, 4	+375291234586	2025-06-17	1800.00	16
21	Светлана	Алексеева	Анатольевна	\\320	1990-11-07	Минск, ул. Горького, 4	+375291234587	2025-11-07	1400.00	22
22	Анатолий	Рябов	Григорьевич	\\320	1983-08-29	Минск, ул. Воронянского, 7	+375291234588	2025-08-29	2300.00	24
23	Василий	Тихонов	Артемович	\\320	1987-06-23	Минск, ул. Московская, 15	+375291234589	2025-06-23	1650.00	1
24	Николай	Савельев	Павлович	\\320	1985-02-14	Минск, ул. Романовская Слобода, 6	+375291234590	2025-02-14	1750.00	3
25	Глеб	Новиков	Игоревич	\\320	1993-10-05	Минск, ул. Партизанский проспект, 22	+375291234591	2025-10-05	1350.00	4
26	Олег	Фомин	Александрович	\\320	1988-12-30	Минск, ул. Кальварийская, 8	+375291234592	2025-12-30	1600.00	8
\.


--
-- TOC entry 5047 (class 0 OID 45287)
-- Dependencies: 231
-- Data for Name: position; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."position" (id, name) FROM stdin;
1	Автослесарь
2	Механик
3	Диагност
4	Шиномонтажник
5	Кузовщик
6	Техник по ремонту
7	Техник-электрик
8	Менеджер
9	Администратор
10	Директор
11	Кладовщик
12	Техник по обслуживанию
13	Программист
14	Охранник
15	Грузчик
16	Мойщик
17	Инженер по ремонту
18	Специалист по безопасности
19	Контролер качества
20	Руководитель службы качества
21	Координатор
22	Кассир
23	Маркетолог
24	Менеджер по закупкам
25	Водитель
26	Секретарь
\.


--
-- TOC entry 5054 (class 0 OID 45310)
-- Dependencies: 238
-- Data for Name: service; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.service (id, name, description, price, warranty_period) FROM stdin;
1	Замена масла	Полная замена моторного масла с заменой фильтра	120.00	6 months
2	Диагностика двигателя	Компьютерная диагностика работы двигателя	80.00	\N
3	Замена тормозных колодок	Передние или задние, в зависимости от износа	90.00	3 months
4	Замена тормозных дисков	Установка новых тормозных дисков	250.00	6 months
5	Регулировка развала-схождения	\N	70.00	\N
6	Замена ремня ГРМ	С заменой натяжного ролика	300.00	12 months
7	Ремонт подвески	Диагностика и замена амортизаторов	220.00	6 months
8	Замена аккумулятора	Проверка заряда и установка нового АКБ	50.00	6 months
9	Диагностика электрики	\N	100.00	\N
10	Замена свечей зажигания	Профилактика системы зажигания	60.00	6 months
11	Чистка инжектора	Промывка топливной системы	90.00	3 months
12	Заправка кондиционера	Проверка и заправка хладагентом	110.00	6 months
13	Полировка кузова	Восстановление блеска и защита ЛКП	180.00	6 months
14	Шумоизоляция	Улучшение шумоизоляции салона	500.00	12 months
15	Замена масла в коробке передач	Полная или частичная замена	180.00	6 months
16	Ремонт стартера	Разборка, диагностика и ремонт	140.00	3 months
17	Ремонт генератора	Восстановление работоспособности	170.00	3 months
18	Замена топливного фильтра	\N	50.00	6 months
19	Ремонт рулевой рейки	Замена или восстановление механизма	400.00	6 months
20	Промывка радиатора	Очистка системы охлаждения	90.00	\N
21	Замена стекол	Переднее, боковое или заднее	350.00	12 months
22	Антикоррозийная обработка	Защита кузова от ржавчины	450.00	24 months
23	Диагностика ходовой части	Проверка износа деталей подвески	85.00	\N
24	Ремонт системы охлаждения	Диагностика и устранение утечек	275.00	6 months
25	Замена ремня генератора	Новый ремень с регулировкой натяжения	95.00	6 months
26	Установка сигнализации	Монтаж и настройка охранной системы	600.00	12 months
\.


--
-- TOC entry 5059 (class 0 OID 45325)
-- Dependencies: 243
-- Data for Name: service_consumable_material; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.service_consumable_material (service_id, consumable_material_id, amount) FROM stdin;
1	1	4.00
1	4	1.00
3	13	1.00
4	14	1.00
6	9	1.00
6	26	1.00
8	19	1.00
10	8	1.00
11	5	1.00
12	17	2.00
15	1	2.00
18	6	1.00
20	3	2.00
22	25	2.00
23	16	2.00
24	21	1.00
25	3	1.00
26	10	1.00
2	2	1.00
5	7	1.00
7	12	1.00
9	11	1.00
13	20	1.00
14	22	1.00
16	18	1.00
17	23	1.00
\.


--
-- TOC entry 5065 (class 0 OID 45343)
-- Dependencies: 249
-- Data for Name: service_employee; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.service_employee (service_id, employee_id) FROM stdin;
1	3
2	5
3	7
4	7
5	8
6	6
7	6
8	4
9	10
10	9
11	12
12	12
13	14
14	15
15	3
16	12
17	18
18	7
19	5
20	14
21	8
22	16
23	17
24	11
25	13
26	9
\.


--
-- TOC entry 5050 (class 0 OID 45295)
-- Dependencies: 234
-- Data for Name: work_area; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.work_area (id, name, status, last_service_date, work_area_type_id) FROM stdin;
1	Подъемник №1	Работает	2024-01-15	1
2	Подъемник №2	На обслуживании	2024-02-20	1
3	Подъемник №3	Работает	2024-01-25	1
4	Подъемник №4	Работает	2024-02-05	1
5	Подъемник №5	Не работает	2024-02-10	1
6	Мойка №1	Работает	2024-02-10	2
7	Мойка №2	Не работает	2023-12-05	2
8	Мойка №3	Работает	2024-02-15	2
9	Мойка №4	На обслуживании	2024-01-30	2
10	Зона диагностики 1	Работает	2024-02-18	3
11	Зона диагностики 2	Работает	2024-01-30	3
12	Зона диагностики 3	На обслуживании	2024-02-25	3
13	Зона диагностики 4	Работает	2024-02-12	3
14	Шиномонтаж 1	Работает	2024-02-22	4
15	Шиномонтаж 2	Работает	2024-02-05	4
16	Шиномонтаж 3	Не работает	2024-01-28	4
17	Шиномонтаж 4	Работает	2024-02-14	4
18	Кузовной ремонт 1	На обслуживании	2024-02-12	5
19	Кузовной ремонт 2	Работает	2024-01-28	5
20	Кузовной ремонт 3	Работает	2024-02-01	5
21	Кузовной ремонт 4	Не работает	2024-01-20	5
22	Слесарный участок 1	Работает	2024-02-08	6
23	Слесарный участок 2	Работает	2024-01-20	6
24	Слесарный участок 3	Не работает	2023-11-25	6
25	Слесарный участок 4	Работает	2024-02-17	6
26	Кузовной ремонт 5	Работает	2025-01-11	5
\.


--
-- TOC entry 5062 (class 0 OID 45334)
-- Dependencies: 246
-- Data for Name: work_area_service; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.work_area_service (work_area_id, service_id) FROM stdin;
1	1
1	2
2	3
2	4
3	5
3	6
4	7
4	8
5	9
5	10
6	11
6	12
1	13
1	14
2	15
2	16
3	17
3	18
4	19
4	20
5	21
5	22
6	23
6	24
6	25
6	26
\.


--
-- TOC entry 5052 (class 0 OID 45303)
-- Dependencies: 236
-- Data for Name: work_area_type; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.work_area_type (id, name) FROM stdin;
1	Подъемник
2	Мойка
3	Диагностика
4	Шиномонтаж
5	Кузовной ремонт
6	Слесарный участок
7	Электрика
8	Развал-схождение
9	Тормозной стенд
10	Зона технического осмотра
11	Стенд для проверки инжектора
12	Моторный цех
13	Аккумуляторный участок
14	Тест-драйвовая зона
15	Зона подготовки к покраске
16	Покрасочная камера
17	Полировочный участок
18	Склад запчастей
19	Склад расходников
20	Приемка автомобилей
21	Зона выдачи автомобилей
22	Комната отдыха персонала
23	Зона ожидания клиентов
24	Административный офис
25	Учебный класс для сотрудников
26	Экспериментальная зона
\.


--
-- TOC entry 5042 (class 0 OID 45270)
-- Dependencies: 226
-- Data for Name: work_order; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.work_order (id, public_id, created_at, competed_at, comment, total_cost, car_id) FROM stdin;
1	WO-2024-001	2024-02-01	2024-02-02	Плановое техническое обслуживание	350.00	2
2	WO-2024-002	2024-02-03	2024-02-04	Замена масла и фильтров	200.00	3
3	WO-2024-003	2024-02-05	2024-02-06	Замена тормозных колодок	180.00	4
4	WO-2024-004	2025-01-07	\N	Диагностика подвески	\N	5
5	WO-2024-005	2024-02-08	2024-02-09	Замена ремня ГРМ	400.00	6
6	WO-2024-006	2024-02-10	2024-02-12	Комплексный ремонт сцепления	750.00	7
7	WO-2024-007	2024-02-13	2024-02-14	Ремонт выхлопной системы	220.00	8
8	WO-2024-008	2024-02-15	2024-02-16	Компьютерная диагностика	120.00	9
9	WO-2024-009	2024-02-17	2024-02-18	Замена аккумулятора	260.00	10
10	WO-2024-010	2025-01-19	\N	Осмотр перед продажей	\N	11
11	WO-2024-011	2024-02-20	2024-02-21	Замена рулевых наконечников	340.00	12
12	WO-2024-012	2024-02-22	2024-02-23	Обслуживание кондиционера	280.00	13
13	WO-2024-013	2024-02-24	2024-02-25	Покраска крыла	500.00	14
14	WO-2024-014	2025-01-26	\N	Диагностика вибрации кузова	\N	15
15	WO-2024-015	2024-02-27	2024-02-28	Замена тормозных дисков	350.00	16
16	WO-2024-016	2024-02-29	2024-03-01	Регулировка развала-схождения	120.00	17
17	WO-2024-017	2025-02-02	\N	Проверка уровня жидкостей	\N	18
18	WO-2024-018	2024-03-03	2024-03-04	Замена топливного фильтра	150.00	19
19	WO-2024-019	2024-03-05	2024-03-06	Замена дворников	50.00	20
20	WO-2024-020	2025-02-07	\N	Проверка коробки передач	\N	21
21	WO-2024-021	2024-03-08	2024-03-09	Промывка радиатора	130.00	22
22	WO-2024-022	2024-03-10	2024-03-11	Замена свечей зажигания	90.00	23
23	WO-2024-023	2025-02-12	2024-03-13	Антикоррозийная обработка	250.00	24
24	WO-2024-024	2024-03-14	\N	Кузовной ремонт	\N	25
25	WO-2024-025	2024-03-15	2024-03-16	Полная диагностика автомобиля	180.00	26
26	WO-2024-026	2025-02-17	\N	Ремонт передней подвески	\N	2
\.


--
-- TOC entry 5105 (class 0 OID 0)
-- Dependencies: 222
-- Name: car_client_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.car_client_id_seq', 1, false);


--
-- TOC entry 5106 (class 0 OID 0)
-- Dependencies: 221
-- Name: car_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.car_id_seq', 26, true);


--
-- TOC entry 5107 (class 0 OID 0)
-- Dependencies: 219
-- Name: client_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.client_id_seq', 27, true);


--
-- TOC entry 5108 (class 0 OID 0)
-- Dependencies: 255
-- Name: completed_service_employee_completed_service_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.completed_service_employee_completed_service_id_seq', 1, false);


--
-- TOC entry 5109 (class 0 OID 0)
-- Dependencies: 256
-- Name: completed_service_employee_employee_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.completed_service_employee_employee_id_seq', 1, false);


--
-- TOC entry 5110 (class 0 OID 0)
-- Dependencies: 250
-- Name: completed_service_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.completed_service_id_seq', 62, true);


--
-- TOC entry 5111 (class 0 OID 0)
-- Dependencies: 253
-- Name: completed_service_service_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.completed_service_service_id_seq', 1, false);


--
-- TOC entry 5112 (class 0 OID 0)
-- Dependencies: 252
-- Name: completed_service_work_area_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.completed_service_work_area_id_seq', 1, false);


--
-- TOC entry 5113 (class 0 OID 0)
-- Dependencies: 251
-- Name: completed_service_work_order_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.completed_service_work_order_id_seq', 1, false);


--
-- TOC entry 5114 (class 0 OID 0)
-- Dependencies: 239
-- Name: consumable_material_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.consumable_material_id_seq', 26, true);


--
-- TOC entry 5115 (class 0 OID 0)
-- Dependencies: 227
-- Name: employee_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.employee_id_seq', 26, true);


--
-- TOC entry 5116 (class 0 OID 0)
-- Dependencies: 228
-- Name: employee_position_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.employee_position_id_seq', 1, false);


--
-- TOC entry 5117 (class 0 OID 0)
-- Dependencies: 230
-- Name: position_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.position_id_seq', 26, true);


--
-- TOC entry 5118 (class 0 OID 0)
-- Dependencies: 242
-- Name: service_consumable_material_consumable_material_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.service_consumable_material_consumable_material_id_seq', 1, false);


--
-- TOC entry 5119 (class 0 OID 0)
-- Dependencies: 241
-- Name: service_consumable_material_service_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.service_consumable_material_service_id_seq', 1, false);


--
-- TOC entry 5120 (class 0 OID 0)
-- Dependencies: 248
-- Name: service_employee_employee_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.service_employee_employee_id_seq', 1, false);


--
-- TOC entry 5121 (class 0 OID 0)
-- Dependencies: 247
-- Name: service_employee_service_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.service_employee_service_id_seq', 1, false);


--
-- TOC entry 5122 (class 0 OID 0)
-- Dependencies: 237
-- Name: service_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.service_id_seq', 26, true);


--
-- TOC entry 5123 (class 0 OID 0)
-- Dependencies: 232
-- Name: work_area_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.work_area_id_seq', 26, true);


--
-- TOC entry 5124 (class 0 OID 0)
-- Dependencies: 245
-- Name: work_area_service_service_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.work_area_service_service_id_seq', 1, false);


--
-- TOC entry 5125 (class 0 OID 0)
-- Dependencies: 244
-- Name: work_area_service_work_area_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.work_area_service_work_area_id_seq', 1, false);


--
-- TOC entry 5126 (class 0 OID 0)
-- Dependencies: 235
-- Name: work_area_type_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.work_area_type_id_seq', 26, true);


--
-- TOC entry 5127 (class 0 OID 0)
-- Dependencies: 233
-- Name: work_area_work_zone_type_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.work_area_work_zone_type_id_seq', 1, false);


--
-- TOC entry 5128 (class 0 OID 0)
-- Dependencies: 225
-- Name: work_order_car_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.work_order_car_id_seq', 1, false);


--
-- TOC entry 5129 (class 0 OID 0)
-- Dependencies: 224
-- Name: work_order_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.work_order_id_seq', 26, true);


--
-- TOC entry 4852 (class 2606 OID 45267)
-- Name: car car_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.car
    ADD CONSTRAINT car_pkey PRIMARY KEY (id);


--
-- TOC entry 4850 (class 2606 OID 45258)
-- Name: client client_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.client
    ADD CONSTRAINT client_pkey PRIMARY KEY (id);


--
-- TOC entry 4874 (class 2606 OID 45500)
-- Name: completed_service_employee completed_service_employee_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.completed_service_employee
    ADD CONSTRAINT completed_service_employee_pkey PRIMARY KEY (completed_service_id, employee_id);


--
-- TOC entry 4872 (class 2606 OID 45362)
-- Name: completed_service completed_service_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.completed_service
    ADD CONSTRAINT completed_service_pkey PRIMARY KEY (id);


--
-- TOC entry 4866 (class 2606 OID 45322)
-- Name: consumable_material consumable_material_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.consumable_material
    ADD CONSTRAINT consumable_material_pkey PRIMARY KEY (id);


--
-- TOC entry 4856 (class 2606 OID 45285)
-- Name: employee employee_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.employee
    ADD CONSTRAINT employee_pkey PRIMARY KEY (id);


--
-- TOC entry 4858 (class 2606 OID 45292)
-- Name: position position_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."position"
    ADD CONSTRAINT position_pkey PRIMARY KEY (id);


--
-- TOC entry 4868 (class 2606 OID 45331)
-- Name: service_consumable_material service_consumable_material_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.service_consumable_material
    ADD CONSTRAINT service_consumable_material_pkey PRIMARY KEY (service_id, consumable_material_id);


--
-- TOC entry 4864 (class 2606 OID 45315)
-- Name: service service_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.service
    ADD CONSTRAINT service_pkey PRIMARY KEY (id);


--
-- TOC entry 4860 (class 2606 OID 45301)
-- Name: work_area work_area_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.work_area
    ADD CONSTRAINT work_area_pkey PRIMARY KEY (id);


--
-- TOC entry 4870 (class 2606 OID 45340)
-- Name: work_area_service work_area_service_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.work_area_service
    ADD CONSTRAINT work_area_service_pkey PRIMARY KEY (work_area_id, service_id);


--
-- TOC entry 4854 (class 2606 OID 45276)
-- Name: work_order work_order_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.work_order
    ADD CONSTRAINT work_order_pkey PRIMARY KEY (id);


--
-- TOC entry 4862 (class 2606 OID 45308)
-- Name: work_area_type work_zone_type_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.work_area_type
    ADD CONSTRAINT work_zone_type_pkey PRIMARY KEY (id);


--
-- TOC entry 4875 (class 2606 OID 45372)
-- Name: car car_client_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.car
    ADD CONSTRAINT car_client_id_fkey FOREIGN KEY (client_id) REFERENCES public.client(id) NOT VALID;


--
-- TOC entry 4888 (class 2606 OID 45501)
-- Name: completed_service_employee completed_service_employee_completed_service_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.completed_service_employee
    ADD CONSTRAINT completed_service_employee_completed_service_id_fkey FOREIGN KEY (completed_service_id) REFERENCES public.completed_service(id);


--
-- TOC entry 4889 (class 2606 OID 45506)
-- Name: completed_service_employee completed_service_employee_employee_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.completed_service_employee
    ADD CONSTRAINT completed_service_employee_employee_id_fkey FOREIGN KEY (employee_id) REFERENCES public.employee(id);


--
-- TOC entry 4885 (class 2606 OID 45427)
-- Name: completed_service completed_service_service_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.completed_service
    ADD CONSTRAINT completed_service_service_id_fkey FOREIGN KEY (service_id) REFERENCES public.service(id) NOT VALID;


--
-- TOC entry 4886 (class 2606 OID 45432)
-- Name: completed_service completed_service_work_area_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.completed_service
    ADD CONSTRAINT completed_service_work_area_id_fkey FOREIGN KEY (work_area_id) REFERENCES public.work_area(id) NOT VALID;


--
-- TOC entry 4887 (class 2606 OID 45422)
-- Name: completed_service completed_service_work_order_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.completed_service
    ADD CONSTRAINT completed_service_work_order_id_fkey FOREIGN KEY (work_order_id) REFERENCES public.work_order(id) NOT VALID;


--
-- TOC entry 4877 (class 2606 OID 45382)
-- Name: employee employee_position_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.employee
    ADD CONSTRAINT employee_position_id_fkey FOREIGN KEY (position_id) REFERENCES public."position"(id) NOT VALID;


--
-- TOC entry 4879 (class 2606 OID 45397)
-- Name: service_consumable_material service_consumable_material_consumable_material_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.service_consumable_material
    ADD CONSTRAINT service_consumable_material_consumable_material_id_fkey FOREIGN KEY (consumable_material_id) REFERENCES public.consumable_material(id) NOT VALID;


--
-- TOC entry 4880 (class 2606 OID 45392)
-- Name: service_consumable_material service_consumable_material_service_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.service_consumable_material
    ADD CONSTRAINT service_consumable_material_service_id_fkey FOREIGN KEY (service_id) REFERENCES public.service(id) NOT VALID;


--
-- TOC entry 4883 (class 2606 OID 45417)
-- Name: service_employee service_employee_employee_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.service_employee
    ADD CONSTRAINT service_employee_employee_id_fkey FOREIGN KEY (employee_id) REFERENCES public.employee(id) NOT VALID;


--
-- TOC entry 4884 (class 2606 OID 45412)
-- Name: service_employee service_employee_service_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.service_employee
    ADD CONSTRAINT service_employee_service_id_fkey FOREIGN KEY (service_id) REFERENCES public.service(id) NOT VALID;


--
-- TOC entry 4881 (class 2606 OID 45407)
-- Name: work_area_service work_area_service_service_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.work_area_service
    ADD CONSTRAINT work_area_service_service_id_fkey FOREIGN KEY (service_id) REFERENCES public.service(id) NOT VALID;


--
-- TOC entry 4882 (class 2606 OID 45402)
-- Name: work_area_service work_area_service_work_area_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.work_area_service
    ADD CONSTRAINT work_area_service_work_area_id_fkey FOREIGN KEY (work_area_id) REFERENCES public.work_area(id) NOT VALID;


--
-- TOC entry 4878 (class 2606 OID 45387)
-- Name: work_area work_area_work_zone_type_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.work_area
    ADD CONSTRAINT work_area_work_zone_type_id_fkey FOREIGN KEY (work_area_type_id) REFERENCES public.work_area_type(id) NOT VALID;


--
-- TOC entry 4876 (class 2606 OID 45377)
-- Name: work_order work_order_car_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.work_order
    ADD CONSTRAINT work_order_car_id_fkey FOREIGN KEY (car_id) REFERENCES public.car(id) NOT VALID;


-- Completed on 2025-02-27 14:18:51

--
-- PostgreSQL database dump complete
--

