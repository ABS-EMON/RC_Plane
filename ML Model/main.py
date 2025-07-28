from fastapi import FastAPI, HTTPException, Request
from pydantic import BaseModel
import joblib
import numpy as np
from fastapi.middleware.cors import CORSMiddleware
import logging

app = FastAPI()

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

# Add CORS middleware
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Load model and encoders
try:
    model = joblib.load("rc_risk_predictor.pkl")
    le_model = joblib.load("le_model.pkl")
    le_city = joblib.load("le_city.pkl")
    le_state = joblib.load("le_state.pkl")
    le_label = joblib.load("le_label.pkl")
    logger.info("Model and encoders loaded successfully")
except Exception as e:
    logger.error(f"Error loading models: {str(e)}")
    raise RuntimeError("Failed to load models") from e

# Input schema using Pydantic
class FlightInput(BaseModel):
    long: float
    lat: float
    alt: float
    mph: float
    model: str
    reg_city: str
    reg_state: str

@app.middleware("http")
async def log_requests(request: Request, call_next):
    logger.info(f"Incoming request: {request.method} {request.url}")
    response = await call_next(request)
    logger.info(f"Response status: {response.status_code}")
    return response

@app.get("/")
def root():
    return {"message": "RC Jet Risk Prediction API is running."}

@app.options("/predict", include_in_schema=False)
async def options_predict():
    return {"message": "CORS allowed"}

@app.post("/predict")
def predict_risk(data: FlightInput):
    try:
        logger.info(f"Received prediction request: {data.dict()}")

        # Encode categorical fields
        model_encoded = le_model.transform([data.model])[0]
        city_encoded = le_city.transform([data.reg_city])[0]
        state_encoded = le_state.transform([data.reg_state])[0]
        logger.info(f"Encoded values: model={model_encoded}, city={city_encoded}, state={state_encoded}")

        # Prepare input vector
        input_vector = np.array([[data.long, data.lat, data.alt, model_encoded, data.mph, city_encoded, state_encoded]])
        logger.info(f"Input vector: {input_vector}")

        # Predict
        pred = model.predict(input_vector)[0]
        label = le_label.inverse_transform([pred])[0]
        logger.info(f"Prediction result: {label}")

        return {"prediction": label}

    except ValueError as e:
        logger.error(f"Value error: {str(e)}")
        raise HTTPException(status_code=400, detail=f"Invalid input: {str(e)}")
    except Exception as e:
        logger.error(f"Prediction failed: {str(e)}")
        raise HTTPException(status_code=500, detail=f"Prediction error: {str(e)}")